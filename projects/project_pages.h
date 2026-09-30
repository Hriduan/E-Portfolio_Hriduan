// =====================================================
//  project_pages.h  -  THE PAGES THAT SHOW THE PROJECTS
//  - projectTile(): the small card (home page + projects page)
//  - projectsPage(): the page with all the projects
//  - projectPage(i): the detail page of one project
//  The projects themselves come from the projects folder.
// =====================================================
#pragma once
#include <string>
#include "project_loader.h"
#include "../ui/layout.h"
#include "../ui/footer.h"
using namespace std;

// one project tile (used on home and projects page)
string projectTile(const Project& p) {
    string s = "<a class=\"tile reveal\" href=\"project-" + p.slug + ".html\">\n";
    s += "<div class=\"tile-img\"><img src=\"" + assetUrl(p.photos[0].file) + "\" alt=\"" + p.title + "\" loading=\"lazy\">";
    s += "<span class=\"tile-cat\">" + p.category + "</span></div>\n";
    s += "<div class=\"tile-body\"><h3>" + p.title + "</h3><p>" + p.summary + "</p>";
    s += "<span class=\"more\">View details <b>&rarr;</b></span></div>\n</a>\n";
    return s;
}

// ---------------------- PROJECTS PAGE ----------------------
string projectsPage() {
    string s = startPage("Projects", "projects.html");
    s += pageTitle("My projects", "Things I built with my own hands. Click on a project to see photos and details.");
    s += "<section class=\"wrap section\">\n<div class=\"projects-grid\">\n";
    for (int i = 0; i < (int)projects.size(); i++) {
        s += projectTile(projects[i]);
    }
    s += "</div>\n</section>\n";
    s += ctaHtml();
    s += footerHtml();
    return s;
}

// ---------------------- ONE PROJECT PAGE ----------------------
// i = number of the project in the list (the order of the files in the projects folder)
string projectPage(int i) {
    const Project& p = projects[i];
    string s = startPage(p.title, "projects.html");

    s += "<section class=\"wrap page-hero\">\n<a class=\"crumb\" href=\"projects.html\">&larr; Back to all projects</a>\n";
    s += "<h1>" + p.title + "</h1>\n<p>" + p.summary + "</p>\n</section>\n";

    s += "<section class=\"wrap section\">\n<div class=\"detail\">\n<div>\n";

    // photos
    s += "<div class=\"gallery\" id=\"gallery\">\n";
    for (int k = 0; k < (int)p.photos.size(); k++) {
        s += "<figure class=\"reveal\"><a href=\"#pic-" + to_string(k) + "\"><img src=\"" + assetUrl(p.photos[k].file) + "\" alt=\"" + p.photos[k].caption + "\" loading=\"lazy\">";
        s += "<figcaption>" + p.photos[k].caption + "</figcaption></a></figure>\n";
    }
    s += "</div>\n";
    // the big version of each photo (opens when a photo is clicked, click again to close)
    for (int k = 0; k < (int)p.photos.size(); k++) {
        s += "<a class=\"lightbox\" id=\"pic-" + to_string(k) + "\" href=\"#gallery\"><div><img src=\"" + assetUrl(p.photos[k].file) + "\" alt=\"\"><p>" + p.photos[k].caption + "</p></div></a>\n";
    }

    // text
    s += "<div class=\"text-block\">\n<h2>About this project</h2>\n";
    for (int k = 0; k < (int)p.details.size(); k++) {
        s += "<p>" + p.details[k] + "</p>\n";
    }
    s += "<h2>What it does</h2>\n<ul class=\"check\">\n";
    for (int k = 0; k < (int)p.features.size(); k++) {
        s += "<li>" + p.features[k] + "</li>\n";
    }
    s += "</ul>\n</div>\n</div>\n";

    // side box
    s += "<aside class=\"card side-box reveal\">\n<h3>Type</h3>\n<div class=\"tags\"><span class=\"tag\">" + p.category + "</span></div>\n";
    s += "<h3>Tools and topics</h3>\n<div class=\"tags\">";
    for (int k = 0; k < (int)p.tools.size(); k++) {
        s += "<span class=\"tag\">" + p.tools[k] + "</span>";
    }
    s += "</div>\n<h3>Made by</h3>\n<p>" + FULL_NAME + "</p>\n</aside>\n";
    s += "</div>\n";

    // previous and next project (only when there is more than one project)
    int total = (int)projects.size();
    if (total > 1) {
        int prev = (i + total - 1) % total;
        int next = (i + 1) % total;
        s += "<div class=\"pager\">\n";
        s += "<a href=\"project-" + projects[prev].slug + ".html\"><small>&larr; Previous project</small>" + projects[prev].title + "</a>\n";
        s += "<a class=\"next\" href=\"project-" + projects[next].slug + ".html\"><small>Next project &rarr;</small>" + projects[next].title + "</a>\n";
        s += "</div>\n";
    }
    s += "</section>\n";

    s += footerHtml();
    return s;
}
