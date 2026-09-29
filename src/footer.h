// =====================================================
//  footer.h  -  THE FOOTER OF EVERY PAGE
//  Edit ONLY this file to change the footer.
//  No other file needs to be touched.
//  After editing, build again (see README.md).
// =====================================================
#pragma once
#include <string>
#include "data.h"
#include "layout.h"     // needs LOGO_SVG and navLinks
using namespace std;

// ---------- EASY SETTINGS (just change the words) ----------
// These texts are written into the page as HTML, so &amp; &copy; and simple tags work.

// small text under the logo (first column)
const string FOOTER_ABOUT_TEXT  = FULL_NAME + ", " + ROLE + " at AIUB. Building practical electronics and learning chip design.";

// column headings
const string FOOTER_PAGES_TITLE    = "Pages";
const string FOOTER_PROJECTS_TITLE = "Projects";
const string FOOTER_CONTACT_TITLE  = "Get in touch";

// the bottom line: left text, centre text, right link
const string FOOTER_COPYRIGHT   = "&copy; " + YEAR + " " + FULL_NAME + ". All rights reserved.";
const string FOOTER_CENTER_TEXT = "E-PORTFOLIO WEBSITE";
const string FOOTER_TOP_LABEL   = "Back to top";

// ---------- the footer itself ----------
// Want to add, remove or move something? Change the lines below.
string footerHtml() {
    string s = "</main>\n<footer class=\"footer\">\n<div class=\"wrap\">\n<div class=\"footer-top\">\n";

    // column 1: about
    s += "<div>\n<a class=\"logo\" href=\"index.html\"><span class=\"logo-mark\">" + LOGO_SVG + "</span>" + SITE_NAME + "</a>\n";
    s += "<p>" + FOOTER_ABOUT_TEXT + "</p>\n</div>\n";

    // column 2: pages
    s += "<div>\n<h4>" + FOOTER_PAGES_TITLE + "</h4>\n<ul>\n";
    for (int i = 0; i < (int)navLinks.size(); i++) {
        s += "<li><a href=\"" + navLinks[i].file + "\">" + navLinks[i].label + "</a></li>\n";
    }
    s += "</ul>\n</div>\n";

    // column 3: projects
    s += "<div>\n<h4>" + FOOTER_PROJECTS_TITLE + "</h4>\n<ul>\n";
    for (int i = 0; i < (int)projects.size(); i++) {
        s += "<li><a href=\"project-" + projects[i].slug + ".html\">" + projects[i].title + "</a></li>\n";
    }
    s += "</ul>\n</div>\n";

    // column 4: contact
    s += "<div>\n<h4>" + FOOTER_CONTACT_TITLE + "</h4>\n<ul>\n";
    s += "<li><a href=\"mailto:" + EMAIL + "\">" + EMAIL + "</a></li>\n";
    s += "<li><a href=\"tel:" + PHONE + "\">" + PHONE + "</a></li>\n";
    s += "<li><a href=\"" + LINKEDIN + "\" target=\"_blank\" rel=\"noopener\">LinkedIn</a></li>\n";
    s += "<li><a href=\"" + assetUrl(CV_FILE) + "\" download>Download CV</a></li>\n";
    s += "<li><span style=\"color:var(--muted);font-size:.95rem\">" + LOCATION + "</span></li>\n";
    s += "</ul>\n</div>\n</div>\n";

    // bottom line: left = copyright, centre = FOOTER_CENTER_TEXT, right = back to top
    s += "<div class=\"footer-bottom\">\n<span>" + FOOTER_COPYRIGHT + "</span>\n";
    s += "<span>" + FOOTER_CENTER_TEXT + "</span>\n";
    s += "<a class=\"to-top\" href=\"#top\">" + FOOTER_TOP_LABEL + "</a>\n</div>\n";
    s += "</div>\n</footer>\n</body>\n</html>\n";
    return s;
}
