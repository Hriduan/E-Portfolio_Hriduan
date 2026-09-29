# Hriduan Omor Siam - E-Portfolio

A dark, multipage e-portfolio. **All source files are written in C++.**
The program in `src/` builds the website (the `.html` pages and `style.css`) in the main folder.

> There is **no JavaScript** in this project. The C++ program writes the .html and
> .css files. You never edit them by hand. You edit the C++ files, then build again.
> All animations, the mobile menu and the photo viewer are done with CSS.

## Folder map

```
index.html, about.html, ...   the finished website pages (made by the program)
style.css                     the finished design (made by the program)
assets/                       ALL images + the CV (one folder)
src/                          C++ source: data.h, style.h, layout.h, footer.h, pages.h, main.cpp
```

## Build (2 commands)

Run them from the **main folder** (the one that contains `src` and `assets`):

```
g++ -std=c++17 src/main.cpp -o build_site
./build_site          (Windows: build_site.exe)
```

Then open `index.html` in your browser.

## What to edit

| I want to change...                          | Edit this file  |
|----------------------------------------------|-----------------|
| **the footer (texts, columns, links)**       | `src/footer.h` (nothing else needed) |
| name, email, phone, LinkedIn, about text     | `src/data.h` (part 1 and 2) |
| numbers on home page (CGPA, projects)        | `src/data.h` (part 3) |
| CGPA on the About page (education)           | `src/data.h` (part 6) |
| interests                                    | `src/data.h` (part 4) |
| add / remove / change a project              | `src/data.h` (part 5) |
| education, experience, skills                | `src/data.h` (part 6, 7, 8) |
| colors (violet, gold, background)            | `src/style.h` (top, `:root`) |
| words that change on the home page           | `src/data.h` (`typingWords`) |
| fonts, spacing, sizes                        | `src/style.h` |
| animations and effects                       | `src/style.h` (keyframes at the bottom) |
| menu links, chip drawing                     | `src/layout.h` |
| layout of a page                             | `src/pages.h` |

After every change: build again (the 2 commands above).

## Images and CV

Everything lives in the one `assets/` folder.

- **Project photos:** every project has 4 photos listed in `src/data.h`. For now they are all the demo image.
  To use a real photo, put it in `assets/` with the **same file name**
  (for example `assets/voting-machine-main.jpg`). No build is needed for a photo you replace by name.
- **Profile photo:** replace `assets/profile.jpg`.
- **CV:** replace `assets/Hriduan_CV.pdf` (keep the same file name).
- If a project photo is ever missing, the build copies `assets/demo.jpg` under that name,
  so the website never shows a broken picture.

## Publish on GitHub Pages

1. Upload this whole folder to a new GitHub repository.
2. Open **Settings > Pages**.
3. Under "Build and deployment" choose **Deploy from a branch**, branch `main`, folder `/ (root)`.
4. Save. Your site will be live after a minute.
