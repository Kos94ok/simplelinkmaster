using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace CS_LauncherReborn
{
    public partial class Form1 : Form
    {
        string language = "english";
        int gl_clientResolutionX, gl_clientResolutionY, gl_editorResolutionX, gl_editorResolutionY;
        bool gl_clientFullscreen, gl_clientBorderless, gl_editorFullscreen, gl_editorBorderless;
        bool demoMode = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void updateResolutionValues(ComboBox aspectRatio, ComboBox resolution, bool isEditor)
        {
            int i = 0, selectedIndex = 0;
            string buf;
            // Getting the screen size
            int screenX = Screen.PrimaryScreen.Bounds.Width;
            int screenY = Screen.PrimaryScreen.Bounds.Height;
            // Clearing old data
            resolution.Items.Clear();
            // Filling arrays
            int[,] dataArray = new int[64, 2];
            int index = aspectRatio.SelectedIndex;
            // 4:3 resolutions
            if (index == 0)
            {
                dataArray[i, 0] = 1024; dataArray[i, 1] = 768; i += 1;
                dataArray[i, 0] = 1152; dataArray[i, 1] = 864; i += 1;
                dataArray[i, 0] = 1280; dataArray[i, 1] = 960; i += 1;
                dataArray[i, 0] = 1400; dataArray[i, 1] = 1050; i += 1;
                dataArray[i, 0] = 1600; dataArray[i, 1] = 1200; i += 1;
            }
            // 16:9 resolutions
            else if (index == 1)
            {
                dataArray[i, 0] = 1280; dataArray[i, 1] = 720; i += 1;
                dataArray[i, 0] = 1366; dataArray[i, 1] = 768; i += 1;
                dataArray[i, 0] = 1600; dataArray[i, 1] = 900; i += 1;
                dataArray[i, 0] = 1920; dataArray[i, 1] = 1080; i += 1;
                dataArray[i, 0] = 2560; dataArray[i, 1] = 1440; i += 1;
            }
            // 16:10 resolutions
            else
            {
                dataArray[i, 0] = 1280; dataArray[i, 1] = 800; i += 1;
                dataArray[i, 0] = 1440; dataArray[i, 1] = 900; i += 1;
                dataArray[i, 0] = 1680; dataArray[i, 1] = 1050; i += 1;
                dataArray[i, 0] = 1920; dataArray[i, 1] = 1200; i += 1;
                dataArray[i, 0] = 2560; dataArray[i, 1] = 1600; i += 1;
            }
            // Inserting the data
            for (int y = 0; y < i; y++)
            {
                if (screenX >= dataArray[y, 0] && screenY >= dataArray[y, 1])
                {
                    buf = dataArray[y, 0].ToString() + " x " + dataArray[y, 1].ToString();
                    resolution.Items.Add(buf);
                    if ((!isEditor && dataArray[y, 0] == gl_clientResolutionX && dataArray[y, 1] == gl_clientResolutionY)
                        || (isEditor && dataArray[y, 0] == gl_editorResolutionX && dataArray[y, 1] == gl_editorResolutionY))
                    {
                        selectedIndex = y;
                    }

                }
            }
            // Selecting something
            resolution.SelectedIndex = selectedIndex;
        }

        private int getSelectedResolution(int value, bool isEditor)
        {
            int index, selected, i = 0;
            int[,] dataArray = new int[64, 2];
            if (!isEditor) { index = drop_aspectRatio.SelectedIndex; selected = drop_resolution.SelectedIndex; }
            else { index = drop_aspectRatioEditor.SelectedIndex; selected = drop_resolutionEditor.SelectedIndex; }
            // 4:3 resolutions
            if (index == 0)
            {
                dataArray[i, 0] = 1024; dataArray[i, 1] = 768; i += 1;
                dataArray[i, 0] = 1152; dataArray[i, 1] = 864; i += 1;
                dataArray[i, 0] = 1280; dataArray[i, 1] = 960; i += 1;
                dataArray[i, 0] = 1400; dataArray[i, 1] = 1050; i += 1;
                dataArray[i, 0] = 1600; dataArray[i, 1] = 1200; i += 1;
            }
            // 16:9 resolutions
            else if (index == 1)
            {
                dataArray[i, 0] = 1280; dataArray[i, 1] = 720; i += 1;
                dataArray[i, 0] = 1366; dataArray[i, 1] = 768; i += 1;
                dataArray[i, 0] = 1600; dataArray[i, 1] = 900; i += 1;
                dataArray[i, 0] = 1920; dataArray[i, 1] = 1080; i += 1;
                dataArray[i, 0] = 2560; dataArray[i, 1] = 1440; i += 1;
            }
            // 16:10 resolutions
            else
            {
                dataArray[i, 0] = 1280; dataArray[i, 1] = 800; i += 1;
                dataArray[i, 0] = 1440; dataArray[i, 1] = 900; i += 1;
                dataArray[i, 0] = 1680; dataArray[i, 1] = 1050; i += 1;
                dataArray[i, 0] = 1920; dataArray[i, 1] = 1200; i += 1;
                dataArray[i, 0] = 2560; dataArray[i, 1] = 1600; i += 1;
            }
            // Returning the requested data
            return dataArray[selected, value];
        }

        private void drop_aspectRatio_SelectedIndexChanged(object sender, EventArgs e)
        {
            updateResolutionValues(drop_aspectRatio, drop_resolution, false);
        }

        private void drop_aspectRatioEditor_SelectedIndexChanged(object sender, EventArgs e)
        {
            updateResolutionValues(drop_aspectRatioEditor, drop_resolutionEditor, true);
        }

        private void updateClientSettings()
        {
            string buf;
            Ini myIni = new Ini("client.ini");
            // Fullscreen
            if (gl_clientFullscreen) { buf = " 1"; } else { buf = " 0"; }
            myIni.Write("Fullscreen ", buf, "Display");
            // Borderless
            if (gl_clientBorderless) { buf = " 1"; } else { buf = " 0"; }
            myIni.Write("Borderless ", buf, "Display");
            // ResolutionX
            buf = " " + getSelectedResolution(0, false).ToString();
            myIni.Write("ResolutionX ", buf, "Display");
            // ResolutionY
            buf = " " + getSelectedResolution(1, false).ToString();
            myIni.Write("ResolutionY ", buf, "Display");
            // Force Texture Preload
            if (check_texturePreload.Checked) { buf = " 1"; } else { buf = " 0"; }
            myIni.Write("ForceTexturePreload ", buf, "Gameplay");
            // Force Texture Clear Up
            if (check_textureClearUp.Checked) { buf = " 1"; } else { buf = " 0"; }
            myIni.Write("ForceTextureClearUp ", buf, "Gameplay");
        }

        private void updateEditorSettings()
        {
            string buf;
            Ini myIni = new Ini("editor.ini");
            // Fullscreen
            if (gl_editorFullscreen) { buf = " 1"; } else { buf = " 0"; }
            myIni.Write("Fullscreen ", buf, "Display");
            // Borderless
            if (gl_editorBorderless) { buf = " 1"; } else { buf = " 0"; }
            myIni.Write("Borderless ", buf, "Display");
            // ResolutionX
            buf = " " + getSelectedResolution(0, true).ToString();
            myIni.Write("ResolutionX ", buf, "Display");
            // ResolutionY
            buf = " " + getSelectedResolution(1, true).ToString();
            myIni.Write("ResolutionY ", buf, "Display");
            // Max Undo Points
            buf = " " + edit_maxUndo.Text;
            myIni.Write("MaxUndoPoints ", buf, "User Interface");
            // Auto Create Directories
            if (check_foldersForModules.Checked) { buf = " 1"; } else { buf = " 0"; }
            myIni.Write("AutoCreateDirectories ", buf, "User Interface");
        }

        private void updateGeneralSettings()
        {
            string buf;
            Ini myIni = new Ini("general.ini");
            // Language
            buf = " " + language;
            myIni.Write("Language ", buf, "General");
            // Demo Mode
            if (demoMode) { buf = " 1"; } else { buf = " 0"; }
            myIni.Write("launcher_hideEditor ", buf, "Launcher");
        }

        private void btn_launchClient_Click(object sender, EventArgs e)
        {
            updateClientSettings();
            updateEditorSettings();
            updateGeneralSettings();
            if (File.Exists("client.exe"))
            {
                var proc = new Process();
                proc.StartInfo.FileName = "client.exe";
                proc.Start();
                Application.Exit();
            }
        }

        private void btn_launchEditor_Click(object sender, EventArgs e)
        {
            updateClientSettings();
            updateEditorSettings();
            updateGeneralSettings();
            if (File.Exists("editor.exe"))
            {
                var proc = new Process();
                proc.StartInfo.FileName = "editor.exe";
                proc.Start();
                Application.Exit();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Reading client.ini
            string buf;
            Ini myIni;
            if (File.Exists("client.ini"))
            {
                myIni = new Ini("client.ini");
                buf = myIni.Read("Fullscreen", "Display"); if (buf == "1") { gl_clientFullscreen = true; } else { gl_clientFullscreen = false; }
                buf = myIni.Read("Borderless", "Display"); if (buf == "1") { gl_clientBorderless = true; } else { gl_clientBorderless = false; }
                buf = myIni.Read("ResolutionX", "Display"); gl_clientResolutionX = Int32.Parse(buf);
                buf = myIni.Read("ResolutionY", "Display"); gl_clientResolutionY = Int32.Parse(buf);
                buf = myIni.Read("ForceTexturePreload", "Gameplay");
                if (buf == "1") { check_texturePreload.Checked = true; } else { check_texturePreload.Checked = false; }
                buf = myIni.Read("ForceTextureClearUp", "Gameplay");
                if (buf == "1") { check_textureClearUp.Checked = true; } else { check_textureClearUp.Checked = false; }
            }
            else
            {
                gl_clientFullscreen = true;
                gl_clientBorderless = false;
                gl_clientResolutionX = -1;
                gl_clientResolutionY = -1;
                check_texturePreload.Checked = true;
                check_textureClearUp.Checked = true;
            }
            
            // Reading editor.ini
            if (File.Exists("editor.ini"))
            {
                myIni = new Ini("editor.ini");
                buf = myIni.Read("Fullscreen", "Display"); if (buf == "1") { gl_editorFullscreen = true; } else { gl_editorFullscreen = false; }
                buf = myIni.Read("Borderless", "Display"); if (buf == "1") { gl_editorBorderless = true; } else { gl_editorBorderless = false; }
                buf = myIni.Read("ResolutionX", "Display"); gl_editorResolutionX = Int32.Parse(buf);
                buf = myIni.Read("ResolutionY", "Display"); gl_editorResolutionY = Int32.Parse(buf);
                buf = myIni.Read("autoCreateDirectories", "User Interface");
                if (buf == "1") { check_foldersForModules.Checked = true; } else { check_foldersForModules.Checked = false; }
                buf = myIni.Read("maxUndoPoints", "User Interface"); edit_maxUndo.Text = buf;
            }
            else
            {
                gl_editorFullscreen = true;
                gl_editorBorderless = false;
                gl_editorResolutionX = -1;
                gl_editorResolutionY = -1;
                edit_maxUndo.Text = "100";
                check_foldersForModules.Checked = true;
            }

            if (gl_clientResolutionX == -1 || gl_clientResolutionY == -1)
            {
                gl_clientResolutionX = Screen.PrimaryScreen.Bounds.Width;
                gl_clientResolutionY = Screen.PrimaryScreen.Bounds.Height;
            }
            if (gl_editorResolutionX == -1 || gl_clientResolutionY == -1)
            {
                gl_editorResolutionX = Screen.PrimaryScreen.Bounds.Width;
                gl_editorResolutionY = Screen.PrimaryScreen.Bounds.Height;
            }

            // Setting the default video mode
            if (gl_clientBorderless) { drop_videoMode.SelectedIndex = 2; }
            else if (gl_clientFullscreen) { drop_videoMode.SelectedIndex = 0; }
            else { drop_videoMode.SelectedIndex = 1; }
            if (gl_editorBorderless) { drop_videoModeEditor.SelectedIndex = 2; }
            else if (gl_editorFullscreen) { drop_videoModeEditor.SelectedIndex = 0; }
            else { drop_videoModeEditor.SelectedIndex = 1; }

            // Setting the default aspect ratio
            float aspect = (float)gl_clientResolutionX / gl_clientResolutionY;
            if (System.Math.Abs(aspect - 1.78) < 0.01) { drop_aspectRatio.SelectedIndex = 1; }
            else if (System.Math.Abs(aspect - 1.6) < 0.01) { drop_aspectRatio.SelectedIndex = 2; }
            else { drop_aspectRatio.SelectedIndex = 0; }
            aspect = (float)gl_editorResolutionX / gl_editorResolutionY;
            if (System.Math.Abs(aspect - 1.78) < 0.01) { drop_aspectRatioEditor.SelectedIndex = 1; }
            else if (System.Math.Abs(aspect - 1.6) < 0.01) { drop_aspectRatioEditor.SelectedIndex = 2; }
            else { drop_aspectRatioEditor.SelectedIndex = 0; }

            // Reading the general.ini
            if (File.Exists("general.ini"))
            {
                myIni = new Ini("general.ini");
                language = myIni.Read("Language", "General");
                buf = myIni.Read("launcher_hideEditor", "Launcher"); if (buf == "1") { demoMode = true; } else { demoMode = false; }
            }

            if (language == "russian") { drop_language.SelectedIndex = 1; }
            else { drop_language.SelectedIndex = 0; }

            // Enabling the demo mode
            if (demoMode)
            {
                btn_launchEditor.Hide();
                tabControl1.TabPages.RemoveAt(1);
                // Adding the adventure logo
                picture_logo.ImageLocation = "Data//Textures//UI_logo_adventure.png";
                picture_logo.SizeMode = PictureBoxSizeMode.Zoom;
                if (File.Exists("Data//Textures//UI_icon_adventure.ico"))
                {
                    this.Icon = new System.Drawing.Icon("Data//Textures//UI_icon_adventure.ico");
                }
            }
            else
            {
                // Adding the Simple Link Master logo
                picture_logo.ImageLocation = "Data//Textures//UI_logo_editor.png";
                picture_logo.SizeMode = PictureBoxSizeMode.Zoom;
            }

            updateLanguage();
        }

        private void drop_videoMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (drop_videoMode.SelectedIndex == 0) { gl_clientBorderless = false; gl_clientFullscreen = true; }
            else if (drop_videoMode.SelectedIndex == 1) { gl_clientBorderless = false; gl_clientFullscreen = false; }
            else { gl_clientBorderless = true; gl_clientFullscreen = false; }
        }

        private void drop_videoModeEditor_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (drop_videoModeEditor.SelectedIndex == 0) { gl_editorBorderless = false; gl_editorFullscreen = true; }
            else if (drop_videoModeEditor.SelectedIndex == 1) { gl_editorBorderless = false; gl_editorFullscreen = false; }
            else { gl_editorBorderless = true; gl_editorFullscreen = false; }
        }

        private void updateLanguage()
        {
            // Regular data
            if (language == "russian")
            {
                label_lang.Text = "Язык:";
                label_cl_mode.Text = "Режим экрана:";
                label_cl_aspect.Text = "Соотношение сторон:";
                label_cl_resolution.Text = "Разрешение:";
                label_ed_mode.Text = "Режим экрана:";
                label_ed_aspect.Text = "Соотношение сторон:";
                label_ed_resolution.Text = "Разрешение:";
                label_ed_maxundo.Text = "Лимит действий:";
                drop_videoMode.Items[0] = "Полноэкранный";
                drop_videoMode.Items[1] = "Оконный";
                drop_videoMode.Items[2] = "Псевдо-полноэкранный";
                drop_videoModeEditor.Items[0] = "Полноэкранный";
                drop_videoModeEditor.Items[1] = "Оконный";
                drop_videoModeEditor.Items[2] = "Псевдо-полноэкранный";
                check_foldersForModules.Text = "Создавать папки для сохранений";
                check_textureClearUp.Text = "Выгружать текстуры при выходе";
                check_texturePreload.Text = "Загружать все текстуры при запуске";
                // Demo mode
                if (demoMode)
                {
                    btn_launchClient.Text = "Запуск!";
                    tabPage1.Text = "Настройки";
                    this.Text = "Когда Будда вышел покурить...";
                }
                // Normal mode
                else
                {
                    btn_launchClient.Text = "Запустить клиент";
                    btn_launchEditor.Text = "Запустить редактор";
                    tabPage1.Text = "Клиент";
                    tabPage2.Text = "Редактор";
                }
            }
            else
            {
                label_lang.Text = "Language:";
                label_cl_mode.Text = "Screen Mode:";
                label_cl_aspect.Text = "Aspect Ratio:";
                label_cl_resolution.Text = "Resolution:";
                label_ed_mode.Text = "Screen Mode:";
                label_ed_aspect.Text = "Aspect Ratio:";
                label_ed_resolution.Text = "Resolution:";
                label_ed_maxundo.Text = "Max Undo Points:";
                drop_videoMode.Items[0] = "Fullscreen";
                drop_videoMode.Items[1] = "Windowed";
                drop_videoMode.Items[2] = "Borderless";
                drop_videoModeEditor.Items[0] = "Fullscreen";
                drop_videoModeEditor.Items[1] = "Windowed";
                drop_videoModeEditor.Items[2] = "Borderless";
                check_foldersForModules.Text = "Create Folders for Modules";
                check_textureClearUp.Text = "Force Texture Clear Up";
                check_texturePreload.Text = "Force Texture Preload";
                // Demo mode
                if (demoMode)
                {
                    btn_launchClient.Text = "Launch!";
                    tabPage1.Text = "Settings";
                    this.Text = "When Budda is out for a smoke...";
                }
                // Normal mode
                else
                {
                    btn_launchClient.Text = "Launch client";
                    btn_launchEditor.Text = "Launch editor";
                    tabPage1.Text = "Client";
                    tabPage2.Text = "Editor";
                }
            }
        }

        private void drop_language_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (drop_language.SelectedIndex == 0) { language = "english"; }
            else if (drop_language.SelectedIndex == 1) { language = "russian"; }

            updateLanguage();
        }
    }
}
