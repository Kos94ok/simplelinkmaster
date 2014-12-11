namespace CS_LauncherReborn
{
    partial class Form1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btn_launchClient = new System.Windows.Forms.Button();
            this.btn_launchEditor = new System.Windows.Forms.Button();
            this.label_cl_mode = new System.Windows.Forms.Label();
            this.label_cl_aspect = new System.Windows.Forms.Label();
            this.drop_videoMode = new System.Windows.Forms.ComboBox();
            this.drop_aspectRatio = new System.Windows.Forms.ComboBox();
            this.drop_resolution = new System.Windows.Forms.ComboBox();
            this.label_cl_resolution = new System.Windows.Forms.Label();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.check_textureClearUp = new System.Windows.Forms.CheckBox();
            this.check_texturePreload = new System.Windows.Forms.CheckBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.label_ed_maxundo = new System.Windows.Forms.Label();
            this.edit_maxUndo = new System.Windows.Forms.TextBox();
            this.check_foldersForModules = new System.Windows.Forms.CheckBox();
            this.label_ed_mode = new System.Windows.Forms.Label();
            this.drop_videoModeEditor = new System.Windows.Forms.ComboBox();
            this.label_ed_resolution = new System.Windows.Forms.Label();
            this.drop_aspectRatioEditor = new System.Windows.Forms.ComboBox();
            this.label_ed_aspect = new System.Windows.Forms.Label();
            this.drop_resolutionEditor = new System.Windows.Forms.ComboBox();
            this.picture_logo = new System.Windows.Forms.PictureBox();
            this.label_lang = new System.Windows.Forms.Label();
            this.drop_language = new System.Windows.Forms.ComboBox();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picture_logo)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_launchClient
            // 
            this.btn_launchClient.Location = new System.Drawing.Point(13, 499);
            this.btn_launchClient.Margin = new System.Windows.Forms.Padding(4);
            this.btn_launchClient.Name = "btn_launchClient";
            this.btn_launchClient.Size = new System.Drawing.Size(166, 28);
            this.btn_launchClient.TabIndex = 0;
            this.btn_launchClient.Text = "Launch Client";
            this.btn_launchClient.UseVisualStyleBackColor = true;
            this.btn_launchClient.Click += new System.EventHandler(this.btn_launchClient_Click);
            // 
            // btn_launchEditor
            // 
            this.btn_launchEditor.Location = new System.Drawing.Point(228, 499);
            this.btn_launchEditor.Margin = new System.Windows.Forms.Padding(4);
            this.btn_launchEditor.Name = "btn_launchEditor";
            this.btn_launchEditor.Size = new System.Drawing.Size(166, 28);
            this.btn_launchEditor.TabIndex = 1;
            this.btn_launchEditor.Text = "Launch Editor";
            this.btn_launchEditor.UseVisualStyleBackColor = true;
            this.btn_launchEditor.Click += new System.EventHandler(this.btn_launchEditor_Click);
            // 
            // label_cl_mode
            // 
            this.label_cl_mode.AutoSize = true;
            this.label_cl_mode.Location = new System.Drawing.Point(8, 11);
            this.label_cl_mode.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_cl_mode.Name = "label_cl_mode";
            this.label_cl_mode.Size = new System.Drawing.Size(96, 17);
            this.label_cl_mode.TabIndex = 3;
            this.label_cl_mode.Text = "Screen Mode:";
            // 
            // label_cl_aspect
            // 
            this.label_cl_aspect.AutoSize = true;
            this.label_cl_aspect.Location = new System.Drawing.Point(8, 44);
            this.label_cl_aspect.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_cl_aspect.Name = "label_cl_aspect";
            this.label_cl_aspect.Size = new System.Drawing.Size(92, 17);
            this.label_cl_aspect.TabIndex = 4;
            this.label_cl_aspect.Text = "Aspect Ratio:";
            // 
            // drop_videoMode
            // 
            this.drop_videoMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.drop_videoMode.FormattingEnabled = true;
            this.drop_videoMode.Items.AddRange(new object[] {
            "Fullscreen",
            "Window",
            "Borderless"});
            this.drop_videoMode.Location = new System.Drawing.Point(180, 7);
            this.drop_videoMode.Margin = new System.Windows.Forms.Padding(4);
            this.drop_videoMode.Name = "drop_videoMode";
            this.drop_videoMode.Size = new System.Drawing.Size(160, 24);
            this.drop_videoMode.TabIndex = 5;
            this.drop_videoMode.SelectedIndexChanged += new System.EventHandler(this.drop_videoMode_SelectedIndexChanged);
            // 
            // drop_aspectRatio
            // 
            this.drop_aspectRatio.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.drop_aspectRatio.FormattingEnabled = true;
            this.drop_aspectRatio.Items.AddRange(new object[] {
            "4:3",
            "16:9",
            "16:10"});
            this.drop_aspectRatio.Location = new System.Drawing.Point(180, 41);
            this.drop_aspectRatio.Margin = new System.Windows.Forms.Padding(4);
            this.drop_aspectRatio.Name = "drop_aspectRatio";
            this.drop_aspectRatio.Size = new System.Drawing.Size(160, 24);
            this.drop_aspectRatio.TabIndex = 6;
            this.drop_aspectRatio.SelectedIndexChanged += new System.EventHandler(this.drop_aspectRatio_SelectedIndexChanged);
            // 
            // drop_resolution
            // 
            this.drop_resolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.drop_resolution.FormattingEnabled = true;
            this.drop_resolution.Location = new System.Drawing.Point(180, 74);
            this.drop_resolution.Margin = new System.Windows.Forms.Padding(4);
            this.drop_resolution.Name = "drop_resolution";
            this.drop_resolution.Size = new System.Drawing.Size(160, 24);
            this.drop_resolution.TabIndex = 7;
            // 
            // label_cl_resolution
            // 
            this.label_cl_resolution.AutoSize = true;
            this.label_cl_resolution.Location = new System.Drawing.Point(8, 78);
            this.label_cl_resolution.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_cl_resolution.Name = "label_cl_resolution";
            this.label_cl_resolution.Size = new System.Drawing.Size(79, 17);
            this.label_cl_resolution.TabIndex = 8;
            this.label_cl_resolution.Text = "Resolution:";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(13, 178);
            this.tabControl1.Margin = new System.Windows.Forms.Padding(4);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(381, 314);
            this.tabControl1.TabIndex = 9;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.check_textureClearUp);
            this.tabPage1.Controls.Add(this.check_texturePreload);
            this.tabPage1.Controls.Add(this.label_cl_mode);
            this.tabPage1.Controls.Add(this.label_cl_resolution);
            this.tabPage1.Controls.Add(this.label_cl_aspect);
            this.tabPage1.Controls.Add(this.drop_resolution);
            this.tabPage1.Controls.Add(this.drop_videoMode);
            this.tabPage1.Controls.Add(this.drop_aspectRatio);
            this.tabPage1.Location = new System.Drawing.Point(4, 25);
            this.tabPage1.Margin = new System.Windows.Forms.Padding(4);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(4);
            this.tabPage1.Size = new System.Drawing.Size(373, 285);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Client";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // check_textureClearUp
            // 
            this.check_textureClearUp.AutoSize = true;
            this.check_textureClearUp.Location = new System.Drawing.Point(12, 149);
            this.check_textureClearUp.Margin = new System.Windows.Forms.Padding(4);
            this.check_textureClearUp.Name = "check_textureClearUp";
            this.check_textureClearUp.Size = new System.Drawing.Size(174, 21);
            this.check_textureClearUp.TabIndex = 10;
            this.check_textureClearUp.Text = "Force Texture Clear Up";
            this.check_textureClearUp.UseVisualStyleBackColor = true;
            // 
            // check_texturePreload
            // 
            this.check_texturePreload.AutoSize = true;
            this.check_texturePreload.Location = new System.Drawing.Point(12, 121);
            this.check_texturePreload.Margin = new System.Windows.Forms.Padding(4);
            this.check_texturePreload.Name = "check_texturePreload";
            this.check_texturePreload.Size = new System.Drawing.Size(168, 21);
            this.check_texturePreload.TabIndex = 9;
            this.check_texturePreload.Text = "Force Texture Preload";
            this.check_texturePreload.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.label_ed_maxundo);
            this.tabPage2.Controls.Add(this.edit_maxUndo);
            this.tabPage2.Controls.Add(this.check_foldersForModules);
            this.tabPage2.Controls.Add(this.label_ed_mode);
            this.tabPage2.Controls.Add(this.drop_videoModeEditor);
            this.tabPage2.Controls.Add(this.label_ed_resolution);
            this.tabPage2.Controls.Add(this.drop_aspectRatioEditor);
            this.tabPage2.Controls.Add(this.label_ed_aspect);
            this.tabPage2.Controls.Add(this.drop_resolutionEditor);
            this.tabPage2.Location = new System.Drawing.Point(4, 25);
            this.tabPage2.Margin = new System.Windows.Forms.Padding(4);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(4);
            this.tabPage2.Size = new System.Drawing.Size(373, 285);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Editor";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // label_ed_maxundo
            // 
            this.label_ed_maxundo.AutoSize = true;
            this.label_ed_maxundo.Location = new System.Drawing.Point(8, 153);
            this.label_ed_maxundo.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_ed_maxundo.Name = "label_ed_maxundo";
            this.label_ed_maxundo.Size = new System.Drawing.Size(118, 17);
            this.label_ed_maxundo.TabIndex = 18;
            this.label_ed_maxundo.Text = "Max Undo Points:";
            // 
            // edit_maxUndo
            // 
            this.edit_maxUndo.Location = new System.Drawing.Point(180, 149);
            this.edit_maxUndo.Margin = new System.Windows.Forms.Padding(4);
            this.edit_maxUndo.Name = "edit_maxUndo";
            this.edit_maxUndo.Size = new System.Drawing.Size(160, 22);
            this.edit_maxUndo.TabIndex = 17;
            // 
            // check_foldersForModules
            // 
            this.check_foldersForModules.AutoSize = true;
            this.check_foldersForModules.Location = new System.Drawing.Point(12, 121);
            this.check_foldersForModules.Margin = new System.Windows.Forms.Padding(4);
            this.check_foldersForModules.Name = "check_foldersForModules";
            this.check_foldersForModules.Size = new System.Drawing.Size(202, 21);
            this.check_foldersForModules.TabIndex = 16;
            this.check_foldersForModules.Text = "Create Folders For Modules";
            this.check_foldersForModules.UseVisualStyleBackColor = true;
            // 
            // label_ed_mode
            // 
            this.label_ed_mode.AutoSize = true;
            this.label_ed_mode.Location = new System.Drawing.Point(8, 11);
            this.label_ed_mode.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_ed_mode.Name = "label_ed_mode";
            this.label_ed_mode.Size = new System.Drawing.Size(96, 17);
            this.label_ed_mode.TabIndex = 10;
            this.label_ed_mode.Text = "Screen Mode:";
            // 
            // drop_videoModeEditor
            // 
            this.drop_videoModeEditor.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.drop_videoModeEditor.FormattingEnabled = true;
            this.drop_videoModeEditor.Items.AddRange(new object[] {
            "Fullscreen",
            "Window",
            "Borderless"});
            this.drop_videoModeEditor.Location = new System.Drawing.Point(180, 7);
            this.drop_videoModeEditor.Margin = new System.Windows.Forms.Padding(4);
            this.drop_videoModeEditor.Name = "drop_videoModeEditor";
            this.drop_videoModeEditor.Size = new System.Drawing.Size(160, 24);
            this.drop_videoModeEditor.TabIndex = 12;
            this.drop_videoModeEditor.SelectedIndexChanged += new System.EventHandler(this.drop_videoModeEditor_SelectedIndexChanged);
            // 
            // label_ed_resolution
            // 
            this.label_ed_resolution.AutoSize = true;
            this.label_ed_resolution.Location = new System.Drawing.Point(8, 78);
            this.label_ed_resolution.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_ed_resolution.Name = "label_ed_resolution";
            this.label_ed_resolution.Size = new System.Drawing.Size(79, 17);
            this.label_ed_resolution.TabIndex = 15;
            this.label_ed_resolution.Text = "Resolution:";
            // 
            // drop_aspectRatioEditor
            // 
            this.drop_aspectRatioEditor.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.drop_aspectRatioEditor.FormattingEnabled = true;
            this.drop_aspectRatioEditor.Items.AddRange(new object[] {
            "4:3",
            "16:9",
            "16:10"});
            this.drop_aspectRatioEditor.Location = new System.Drawing.Point(180, 41);
            this.drop_aspectRatioEditor.Margin = new System.Windows.Forms.Padding(4);
            this.drop_aspectRatioEditor.Name = "drop_aspectRatioEditor";
            this.drop_aspectRatioEditor.Size = new System.Drawing.Size(160, 24);
            this.drop_aspectRatioEditor.TabIndex = 13;
            this.drop_aspectRatioEditor.SelectedIndexChanged += new System.EventHandler(this.drop_aspectRatioEditor_SelectedIndexChanged);
            // 
            // label_ed_aspect
            // 
            this.label_ed_aspect.AutoSize = true;
            this.label_ed_aspect.Location = new System.Drawing.Point(8, 44);
            this.label_ed_aspect.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label_ed_aspect.Name = "label_ed_aspect";
            this.label_ed_aspect.Size = new System.Drawing.Size(92, 17);
            this.label_ed_aspect.TabIndex = 11;
            this.label_ed_aspect.Text = "Aspect Ratio:";
            // 
            // drop_resolutionEditor
            // 
            this.drop_resolutionEditor.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.drop_resolutionEditor.FormattingEnabled = true;
            this.drop_resolutionEditor.Location = new System.Drawing.Point(180, 74);
            this.drop_resolutionEditor.Margin = new System.Windows.Forms.Padding(4);
            this.drop_resolutionEditor.Name = "drop_resolutionEditor";
            this.drop_resolutionEditor.Size = new System.Drawing.Size(160, 24);
            this.drop_resolutionEditor.TabIndex = 14;
            // 
            // picture_logo
            // 
            this.picture_logo.ErrorImage = null;
            this.picture_logo.Location = new System.Drawing.Point(17, 16);
            this.picture_logo.Margin = new System.Windows.Forms.Padding(4);
            this.picture_logo.MaximumSize = new System.Drawing.Size(380, 120);
            this.picture_logo.MinimumSize = new System.Drawing.Size(380, 120);
            this.picture_logo.Name = "picture_logo";
            this.picture_logo.Size = new System.Drawing.Size(380, 120);
            this.picture_logo.TabIndex = 10;
            this.picture_logo.TabStop = false;
            // 
            // label_lang
            // 
            this.label_lang.AutoSize = true;
            this.label_lang.Location = new System.Drawing.Point(14, 149);
            this.label_lang.Name = "label_lang";
            this.label_lang.Size = new System.Drawing.Size(76, 17);
            this.label_lang.TabIndex = 11;
            this.label_lang.Text = "Language:";
            // 
            // drop_language
            // 
            this.drop_language.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.drop_language.FormattingEnabled = true;
            this.drop_language.Items.AddRange(new object[] {
            "English",
            "Русский"});
            this.drop_language.Location = new System.Drawing.Point(197, 146);
            this.drop_language.Margin = new System.Windows.Forms.Padding(4);
            this.drop_language.Name = "drop_language";
            this.drop_language.Size = new System.Drawing.Size(160, 24);
            this.drop_language.TabIndex = 12;
            this.drop_language.SelectedIndexChanged += new System.EventHandler(this.drop_language_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(413, 541);
            this.Controls.Add(this.drop_language);
            this.Controls.Add(this.label_lang);
            this.Controls.Add(this.picture_logo);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.btn_launchEditor);
            this.Controls.Add(this.btn_launchClient);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximumSize = new System.Drawing.Size(431, 585);
            this.MinimumSize = new System.Drawing.Size(431, 585);
            this.Name = "Form1";
            this.Text = "Simple Link Launcher";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picture_logo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_launchClient;
        private System.Windows.Forms.Button btn_launchEditor;
        private System.Windows.Forms.Label label_cl_mode;
        private System.Windows.Forms.Label label_cl_aspect;
        private System.Windows.Forms.ComboBox drop_videoMode;
        private System.Windows.Forms.ComboBox drop_aspectRatio;
        private System.Windows.Forms.ComboBox drop_resolution;
        private System.Windows.Forms.Label label_cl_resolution;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Label label_ed_mode;
        private System.Windows.Forms.ComboBox drop_videoModeEditor;
        private System.Windows.Forms.Label label_ed_resolution;
        private System.Windows.Forms.ComboBox drop_aspectRatioEditor;
        private System.Windows.Forms.Label label_ed_aspect;
        private System.Windows.Forms.ComboBox drop_resolutionEditor;
        private System.Windows.Forms.CheckBox check_textureClearUp;
        private System.Windows.Forms.CheckBox check_texturePreload;
        private System.Windows.Forms.Label label_ed_maxundo;
        private System.Windows.Forms.TextBox edit_maxUndo;
        private System.Windows.Forms.CheckBox check_foldersForModules;
        private System.Windows.Forms.PictureBox picture_logo;
        private System.Windows.Forms.Label label_lang;
        private System.Windows.Forms.ComboBox drop_language;
    }
}

