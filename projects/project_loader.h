// =====================================================
//  project_loader.h  -  FINDS THE PROJECTS BY ITSELF
//  It looks into each project folder and reads its .txt file.
//  One folder = one project. Add a folder and the new project
//  appears everywhere on the website after the next build.
//  (Copy projects/_template to start a new one.)
// =====================================================
#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "../ui/site_data.h"
using namespace std;

struct Photo {
    string file;      // image file name (inside the project's folder)
    string caption;   // text shown under the image
};

struct Project {
    string slug;                // from the file name: project-<slug>.html
    string title;
    string category;
    string summary;             // short text on the project tile
    string imageNote;           // optional image provenance, shown on cards and detail pages
    vector<string> details;     // paragraphs on the project page
    vector<string> features;    // bullet list on the project page
    vector<string> tools;       // small tags on the project page
    vector<Photo> photos;       // first photo is used on the tile
    int order = 1000;           // small number = shown first
    string fileName;            // the .txt file it came from
    string webDir;              // directory containing this project's page assets
};

// the folder where the project files live
const string PROJECTS_DIR = "projects";

// every project found in the folder (filled by loadProjects)
inline vector<Project> projects;

inline string projectAssetUrl(const Project& p, const string& file) {
    return p.webDir + "/" + file;
}

// file name -> safe page name: "Line Follower_Robot" -> "line-follower-robot"
inline string makeSlug(const string& text) {
    string s;
    for (char c : text) {
        c = (char)tolower((unsigned char)c);
        if (isalnum((unsigned char)c)) s += c;
        else if ((c == '-' || c == '_' || c == ' ') && !s.empty() && s.back() != '-') s += '-';
    }
    while (!s.empty() && s.back() == '-') s.pop_back();
    return s;
}

// reads one project file. Returns false if the file cannot be used.
inline bool readProject(const filesystem::path& path, Project& p) {
    TextFile t;
    if (!parseTextFile(path.string(), t)) return false;

    p.fileName = path.filename().string();
    p.webDir = "projects/" + path.parent_path().filename().string();
    p.slug = makeSlug(path.stem().string());
    if (p.slug.empty()) {
        cout << "  WARNING: " << p.fileName << " has no usable name, skipped" << endl;
        return false;
    }

    p.title    = toHtml(t.get("title", path.stem().string()));
    p.category = toHtml(t.get("category", "Project"));
    p.summary  = toHtml(t.get("summary", ""));
    p.imageNote = toHtml(t.get("image_note", ""));
    if (t.get("title").empty())   cout << "  WARNING: " << p.fileName << " has no title" << endl;
    if (t.get("summary").empty()) cout << "  WARNING: " << p.fileName << " has no summary" << endl;

    try { p.order = stoi(t.get("order", "1000")); }
    catch (...) { cout << "  WARNING: " << p.fileName << " has a bad order number" << endl; }

    for (const string& s : t.list("details")) p.details.push_back(toHtml(s));
    for (const string& s : t.list("features")) {
        string f = s;
        if (f.size() > 1 && (f[0] == '-' || f[0] == '*') && f[1] == ' ') f = trim(f.substr(2));   // allow "- item"
        p.features.push_back(toHtml(f));
    }
    for (const string& line : t.list("tools")) {
        for (const string& tool : splitLimit(line, ',', 1000)) if (!tool.empty()) p.tools.push_back(toHtml(tool));
    }
    for (const string& s : t.list("photos")) {
        vector<string> parts = splitLimit(s, '|', 2);
        if (parts[0].empty()) continue;
        p.photos.push_back({parts[0], toHtml(parts.size() > 1 && !parts[1].empty() ? parts[1] : p.title)});
    }
    return true;
}

// looks into the projects folder and fills the "projects" list
inline bool loadProjects() {
    projects.clear();
    if (!filesystem::exists(PROJECTS_DIR)) return false;

    vector<filesystem::path> files;
    for (const auto& folder : filesystem::directory_iterator(PROJECTS_DIR)) {
        if (!folder.is_directory()) continue;
        string folderName = folder.path().filename().string();
        if (folderName.empty() || folderName[0] == '_' || folderName[0] == '.') continue;
        for (const auto& entry : filesystem::directory_iterator(folder.path())) {
            if (!entry.is_regular_file()) continue;
            string name = entry.path().filename().string();
            if (lowerText(entry.path().extension().string()) == ".txt" && !name.empty() && name[0] != '.') {
                files.push_back(entry.path());
            }
        }
    }
    sort(files.begin(), files.end());

    for (const auto& path : files) {
        Project p;
        if (!readProject(path, p)) continue;
        // two files with the same page name: add a number
        string base = p.slug;
        int n = 2;
        bool used = true;
        while (used) {
            used = false;
            for (const Project& other : projects) if (other.slug == p.slug) used = true;
            if (used) p.slug = base + "-" + to_string(n++);
        }
        projects.push_back(p);
    }
    // the "order" number decides the position; same number = file name order
    stable_sort(projects.begin(), projects.end(), [](const Project& a, const Project& b) { return a.order < b.order; });
    return true;
}
