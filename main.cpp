// =====================================================
//  main.cpp  -  RUN THIS PROGRAM TO BUILD THE WEBSITE
//  It reads   about-me.txt   and the files in the   projects   folder,
//  then writes the pages (.html) and the design (style.css)
//  into the MAIN project folder, next to the "assets" folder.
//
//  Run it from the MAIN project folder (the one that contains
//  "ui", "projects" and "assets"), not from inside another folder.
//
//  Build:  g++ -std=c++17 main.cpp -o build_site
//  Run:    ./build_site        (Windows: build_site.exe)
// =====================================================
#include <iostream>
#include <fstream>
#include <filesystem>
#include <set>
#include <string>
#include "ui/site_data.h"        // reads about-me.txt
#include "ui/style.h"            // the design (CSS)
#include "ui/layout.h"           // header, menu, loader, chip
#include "ui/footer.h"           // footer
#include "projects/project_loader.h"   // finds the projects
#include "projects/project_pages.h"    // project tiles and pages
#include "ui/pages.h"            // home, about, experience, contact
using namespace std;
namespace fs = std::filesystem;

// the pages are written here (".", the main project folder)
const string OUT_FOLDER = ".";

// the file with your information
const string ABOUT_FILE = "about-me.txt";

// write a text file into the output folder
void writeFile(const string& name, const string& text) {
    ofstream file(OUT_FOLDER + "/" + name, ios::binary);
    if (!file) {
        cout << "  ERROR: cannot write " << name << endl;
        return;
    }
    file << text;
    cout << "  made " << name << endl;
}

// copy a file (overwrite if it already exists); never stops the build
void copyFile(const string& from, const string& to) {
    if (!fs::exists(from)) {
        cout << "  WARNING: cannot find " << from << endl;
        return;
    }
    try {
        fs::copy_file(from, to, fs::copy_options::overwrite_existing);
    } catch (const exception& e) {
        cout << "  WARNING: could not copy " << from << " (" << e.what() << ")" << endl;
    }
}

int main() {
    cout << "Building the website..." << endl;

    // safety check: the program must be started from the main project folder
    if (!fs::exists(ASSETS_DIR)) {
        cout << "ERROR: cannot find the \"" << ASSETS_DIR << "\" folder here." << endl;
        cout << "Run the program from the main project folder (the one with \"ui\", \"projects\" and \"" << ASSETS_DIR << "\")." << endl;
        return 1;
    }

    // 1. your information
    if (!loadAboutMe(ABOUT_FILE)) {
        cout << "ERROR: cannot find " << ABOUT_FILE << " in the main project folder." << endl;
        return 1;
    }

    // 2. the projects (one file = one project)
    if (!loadProjects()) {
        cout << "ERROR: cannot find the \"" << PROJECTS_DIR << "\" folder." << endl;
        return 1;
    }
    cout << "  found " << projects.size() << " project(s):" << endl;
    for (int i = 0; i < (int)projects.size(); i++) {
        cout << "    " << (i + 1) << ". " << projects[i].title << "  (" << projects[i].fileName << ")" << endl;
    }
    if (projects.empty()) {
        cout << "  WARNING: no project files found. Copy projects/_template.txt to add one." << endl;
    }

    // 3. design and effects (all done with CSS, no JavaScript)
    writeFile("style.css", CSS_TEXT + rotatorCss());

    // 4. normal pages
    writeFile("index.html", homePage());
    writeFile("about.html", aboutPage());
    writeFile("projects.html", projectsPage());
    writeFile("experience.html", experiencePage());
    writeFile("contact.html", contactPage());

    // 5. one page for every project
    set<string> madePages;
    for (int i = 0; i < (int)projects.size(); i++) {
        string name = "project-" + projects[i].slug + ".html";
        writeFile(name, projectPage(i));
        madePages.insert(name);
    }

    // 6. remove old project pages whose project file was deleted
    try {
        for (const auto& entry : fs::directory_iterator(OUT_FOLDER)) {
            string name = entry.path().filename().string();
            if (name.rfind("project-", 0) == 0 && endsWith(name, ".html") && !madePages.count(name)) {
                fs::remove(entry.path());
                cout << "  removed old page " << name << endl;
            }
        }
    } catch (const exception& e) {
        cout << "  WARNING: could not clean old pages (" << e.what() << ")" << endl;
    }

    // 7. profile photo and CV must be inside the assets folder
    for (const string& name : {PROFILE_PHOTO, CV_FILE}) {
        if (!fs::exists(ASSETS_DIR + "/" + name)) {
            cout << "  WARNING: " << ASSETS_DIR << "/" << name << " is missing" << endl;
        }
    }

    // 8. project images live in the same assets folder.
    //    if a photo is missing, the demo image is copied with that name,
    //    so the website never shows a broken picture.
    for (int i = 0; i < (int)projects.size(); i++) {
        for (int k = 0; k < (int)projects[i].photos.size(); k++) {
            string path = ASSETS_DIR + "/" + projects[i].photos[k].file;
            if (!fs::exists(path)) {
                cout << "  no photo found for " << projects[i].photos[k].file << ", using the demo image" << endl;
                copyFile(ASSETS_DIR + "/" + DEMO_IMAGE, path);
            }
        }
    }

    // 9. GitHub Pages should not use Jekyll
    writeFile(".nojekyll", "");

    cout << "Done! Open index.html in your browser." << endl;
    return 0;
}
