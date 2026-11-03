# Update the portfolio from your phone

Your website still uses the same C++17 generator and GitHub Pages workflow. You can edit the text files in Termux then rebuild and push with one command. No Node packages or new website framework are needed.

## 1. Set up Termux

Use a current supported Termux release from its official F-Droid or GitHub distribution. Run:

```bash
pkg update
pkg install git clang python nano openssh
cd "$HOME"
git clone https://github.com/hriduan/E-Portfolio_Hriduan.git
cd E-Portfolio_Hriduan
```

Keep your checkout in Termux home rather than Android shared storage. Shared storage can cause execution and permission problems. Downloaded files can be copied into the checkout after you grant storage access with `termux-setup-storage`.

Set your Git identity once. Use the name and verified email or GitHub-provided private email you want on your commits:

```bash
git config --global user.name "Hriduan Omor Siam"
git config --global user.email "YOUR_COMMIT_EMAIL"
```

Configure GitHub authentication before pushing. HTTPS requires a suitable personal access token instead of your GitHub password. Git may ask for it at the password prompt. Do not put it in a remote URL or a website file. An SSH key registered with your GitHub account is another option. Never share or commit a token or private key. Changing the workflow file may need additional token permission for workflows.

## 2. Apply this updated ZIP to your existing checkout

Extract the delivered ZIP. Copy the contents of its `E-Portfolio_Hriduan-main` folder into your existing repository folder. Include hidden files such as `.github` and `.gitignore`. Do not delete or replace your existing `.git` directory. The ZIP has no Git history.

Before copying make a backup or commit any current work. The copy replaces files with matching names. Review `git diff` before pushing. Do not run `git init` in a second nested folder.

## 3. Edit your information

```bash
cd "$HOME/E-Portfolio_Hriduan"
nano about-me.txt
nano projects/fsmd-controller-asic-fpga.txt
```

Use `about-me.txt` for your profile and education. Each project has a text file under `projects/`. Save photos in `assets/` and update the file names and captions in the project's `[photos]` list. Put a new CV at `assets/Hriduan_CV.pdf` to retain every existing download link.

Project images outside the FSMD project are explicitly labeled AI-generated illustrations. They are not photos of your actual builds. See `IMAGE_PROVENANCE.md`. Replace them with your own photos for documentary evidence. Remove the project's `image_note` only after every illustrative image in that project has been replaced and its captions corrected.

## 4. Check and preview

```bash
bash update check
bash update preview
```

Open `http://127.0.0.1:8080` in the browser on the same phone. Press Ctrl+C in Termux to stop the preview. A different port can be selected with `bash update preview 8081`.

The checker tests local file references and anchors. It does not test external services or verify the truth of project claims. FormSubmit still needs the original email activation and a real online test. Preview does not submit any forms automatically.

## 5. Push your update

```bash
git status
git diff
bash update push "Refresh portfolio information"
```

Running `bash update` without arguments also builds then commits and pushes. The helper stages all changed files just like the original script. Check that no private files are in the repository first. It keeps the existing `vMAJOR.MINOR` tag sequence and uses your current branch and its configured remote instead of forcing a push to `main`.

The script fetches first. If the remote contains changes that are not in your branch it stops without overwriting your work. Commit or stash your local edits then use `git pull --rebase` and resolve any conflicts before trying again. The script never force-pushes. If a push fails your local commit and tag remain available for a retry.

## GitHub Pages

Push to `main` to trigger the supplied GitHub Actions workflow. Other branches can be pushed for review but do not trigger this deployment workflow. The workflow compiles the source and checks the generated pages. It saves any rebuilt files and requests a Pages rebuild.

The existing repository must have Actions enabled with write permission for the workflow and GitHub Pages configured to publish from the root of `main`. Check the Actions and Pages screens after pushing. A successful Git push alone does not confirm that deployment succeeded. If repository rules block bot commits or Pages build requests adjust the repository settings before publishing.

## Troubleshooting

- **Compiler missing:** run `pkg install clang`.
- **Python missing:** run `pkg install python`.
- **Permission denied for the helper:** use `bash update` rather than executing it directly.
- **Not a Git checkout:** return to the folder created by `git clone`.
- **Identity unknown:** configure `user.name` and `user.email`.
- **Authentication failed:** check your GitHub token permissions or SSH key. Never paste a secret into chat.
- **Nothing to commit:** the helper can still push an existing local commit.
- **Remote is ahead:** review and reconcile remote changes before retrying.

The helper has been tested in Linux with a local Git remote. A physical Android device and your live GitHub account were not available for testing.
