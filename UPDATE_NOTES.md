# Portfolio update notes

## Content

The active website now follows `Hriduan_CV_Ulkasemi_DV_v2-1.pdf`. The PDF has replaced `assets/Hriduan_CV.pdf` without changing any download link. The supplied PDF itself has not been edited.

The introduction and About copy now focus on final-year EEE studies at AIUB with a CGPA of 3.87 and an interest in VLSI and design verification. Education includes the completed mandatory VLSI course and elective ASIC Design course confirmed in the conversation. Skills follow the CV's five groups. Leadership entries use the CV's titles and order.

All six project summaries and descriptions have been rewritten in natural first-person language. The existing FSMD measurements and its FPGA timing limitation remain visible. No UVM experience or other unconfirmed qualification has been added. Public website text has been checked for commas immediately before and/or/but.

Long About and project paragraphs are justified on screens at least 768 pixels wide. Phone text remains left-aligned to avoid large gaps between words. A small reduced-motion fix keeps the first rotating role visible when animation is disabled.

## Project images

The profile photograph and all seven remaining FSMD screenshots are unchanged; only the eighth FSMD gallery entry was removed. Twenty repeated placeholder images across the other five projects have been replaced with locally authored technical SVG diagrams. The diagrams identify architecture, electrical relationships or idealized analysis without pretending to be photographs or measured evidence.

These diagrams are not photographs of the actual projects. They must not be used as evidence of a build or measured result. Use your own project photographs and MATLAB screenshots if your professor requires original evidence. See `IMAGE_PROVENANCE.md`.

The homepage now showcases four projects. The Resume page embeds the supplied PDF. Add `assets/Hriduan_intro.mp4` to show a personal introduction video on the homepage; when absent, no empty video placeholder is rendered.

## Phone updates

`bash update build` rebuilds the site. `bash update check` also checks local file references and anchors. `bash update preview` serves the site on the phone's loopback address. `bash update push "message"` builds then commits and pushes through the current Git branch and its remote.

The helper preserves the original version-tag sequence. It does not force-push or automatically resolve conflicts. GitHub authentication must be configured on your phone. It never asks you to store credentials in your website. See `TERMUX.md` for setup and safe ZIP installation into an existing checkout.

The GitHub Actions workflow now includes asset changes as a build trigger and runs the local site checker. Your existing Pages settings and repository permissions still control deployment.

## Preserved scope

The original brand colors, font declarations, logo, photo, chip graphic, page structure, navigation and normal-motion effects are retained. No projects or pages have been removed. The C++ generator and zero-JavaScript approach are unchanged. Legacy files under `src/` are untouched. Build the active site from the root `main.cpp` as documented.

## Checks performed

- C++17 build completed successfully with g++.
- All 11 generated pages passed local link and anchor checks.
- All 11 pages were checked at widths of 1440 and 390 pixels without horizontal overflow or missing image resources after image loading.
- Desktop and phone renders were visually inspected.
- Mobile navigation and gallery opening and closing were tested.
- Required form fields and the existing confirmation state were tested without submitting a message.
- The loopback preview served the updated site successfully.
- The Git helper was tested with isolated local remotes for normal push, version tags, current-branch push, no-change retry, remote-ahead refusal and detached-head refusal.
- The replacement CV matches the uploaded PDF byte for byte. Original FSMD screenshots and profile photo also match their originals.

## Not tested here

No files were pushed to the live GitHub repository. Live Pages deployment and FormSubmit email delivery were not tested. A physical Android phone with Termux was not available. The environment could not load Google Fonts so the offline renders used the existing fallback fonts. The original online font declarations have been retained.

The supplied requirements PDF is a job advertisement rather than a professor's marking rubric. This update aligns the portfolio with the role and supplied CV but does not claim to satisfy an unseen assignment rubric.
