// =====================================================
//  layout.h  -  PARTS THAT ARE SAME ON EVERY PAGE
//  (top of page, loading screen, menu, chip drawing, footer)
// =====================================================
#pragma once
#include <string>
#include <vector>
#include "data.h"
using namespace std;

// ---------- menu links (change names or files here) ----------
struct NavLink {
    string label;
    string file;
};
const vector<NavLink> navLinks = {
    {"Home",       "index.html"},
    {"About",      "about.html"},
    {"Projects",   "projects.html"},
    {"Experience", "experience.html"},
    {"Contact",    "contact.html"}
};

// small chip icon used as logo
const string LOGO_SVG = R"SVG(<svg viewBox="0 0 32 32" width="30" height="30" aria-hidden="true"><rect x="8" y="8" width="16" height="16" rx="3" fill="rgba(139,123,255,.2)" stroke="#8b7bff" stroke-width="2"/><path d="M12 3v5M16 3v5M20 3v5M12 24v5M16 24v5M20 24v5M3 12h5M3 16h5M3 20h5M24 12h5M24 16h5M24 20h5" stroke="#f2c66d" stroke-width="2" stroke-linecap="round"/></svg>)SVG";

// ---------- top of the page ----------
string pageHead(const string& title) {
    string s = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
    s += "<meta charset=\"UTF-8\">\n";
    s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
    s += "<title>" + title + " | " + FULL_NAME + "</title>\n";
    s += "<meta name=\"description\" content=\"E-portfolio of " + FULL_NAME + ", " + ROLE + " at AIUB.\">\n";
    s += "<meta name=\"theme-color\" content=\"#07060d\">\n";
    s += "<link rel=\"icon\" href=\"data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 32 32'%3E%3Crect x='7' y='7' width='18' height='18' rx='4' fill='%238b7bff'/%3E%3C/svg%3E\">\n";
    s += "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">\n";
    s += "<link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>\n";
    s += "<link href=\"https://fonts.googleapis.com/css2?family=DM+Sans:wght@400;500;600&family=Outfit:wght@500;600;700&display=swap\" rel=\"stylesheet\">\n";
    s += "<link rel=\"stylesheet\" href=\"style.css\">\n";
    s += "</head>\n<body id=\"top\">\n";
    return s;
}

// ---------- welcome loading screen ----------
string loaderHtml() {
    string s = "<div id=\"loader\">\n<div class=\"loader-box\">\n<div class=\"load-chip\">\n";
    for (int i = 0; i < 4; i++) {
        string style = " style=\"--i:" + to_string(i) + "\"";
        s += "<i class=\"pt\"" + style + "></i><i class=\"pb\"" + style + "></i>";
        s += "<i class=\"pl\"" + style + "></i><i class=\"pr\"" + style + "></i>\n";
    }
    s += "<span>EEE</span>\n</div>\n";
    s += "<h2 class=\"load-name\">" + FULL_NAME + "</h2>\n";
    s += "<p class=\"load-text\">Powering up the portfolio...</p>\n";
    s += "<div class=\"load-bar\"><div class=\"load-fill\"></div></div>\n</div>\n</div>\n";
    return s;
}

// ---------- menu bar ----------
string navHtml(const string& activeFile) {
    string s = "<div id=\"progress\"></div>\n";
    s += "<header class=\"nav\">\n<div class=\"wrap nav-in\">\n";
    s += "<a class=\"logo\" href=\"index.html\"><span class=\"logo-mark\">" + LOGO_SVG + "</span>" + SITE_NAME + "</a>\n";
    s += "<input type=\"checkbox\" id=\"menuToggle\" class=\"menu-check\" aria-label=\"Open menu\">\n";
    s += "<label for=\"menuToggle\" class=\"menu-btn\"><span></span><span></span><span></span></label>\n";
    s += "<nav id=\"menu\">\n<ul>\n";
    for (int i = 0; i < (int)navLinks.size(); i++) {
        s += "<li><a href=\"" + navLinks[i].file + "\"";
        if (navLinks[i].file == activeFile) s += " class=\"active\"";
        s += ">" + navLinks[i].label + "</a></li>\n";
    }
    s += "</ul>\n</nav>\n</div>\n</header>\n<main>\n";
    return s;
}

// ---------- the semiconductor chip drawing ----------
// One side of the chip (top) is drawn, then it is rotated 4 times.
string chipSide(int rotation) {
    string g = "<g transform=\"rotate(" + to_string(rotation) + " 200 200)\">\n";
    for (int i = 0; i < 8; i++) {
        int x = 140 + i * 17;                 // pin position along the side
        int up = 70 - (i % 4) * 14;           // how high the trace goes
        int shift = (i < 4 ? -1 : 1) * (14 + (i % 4) * 9);   // small bend left or right
        // pin
        g += "<rect class=\"pin\" x=\"" + to_string(x - 3) + "\" y=\"104\" width=\"6\" height=\"16\" rx=\"1.5\"/>\n";
        // trace (a line from the pin going out with one bend)
        g += "<path class=\"trace\" style=\"animation-delay:" + to_string(i * 0.2) + "s\" d=\"M" + to_string(x) + " 104 V" + to_string(up + 20) +
             " L" + to_string(x + shift) + " " + to_string(up) + " V" + to_string(up - 22 + (i % 4) * 4) + "\"/>\n";
        // small round dot at the end of the trace
        g += "<circle class=\"node\" cx=\"" + to_string(x + shift) + "\" cy=\"" + to_string(up - 22 + (i % 4) * 4) + "\" r=\"3\" style=\"animation-delay:" + to_string(i * 0.25) + "s\"/>\n";
    }
    g += "</g>\n";
    return g;
}

string chipSvg() {
    string s = "<svg class=\"chip-svg\" viewBox=\"0 0 400 400\" role=\"img\" aria-label=\"Semiconductor chip drawing\">\n";
    s += chipSide(0) + chipSide(90) + chipSide(180) + chipSide(270);
    s += "<g class=\"chip-core\">\n";
    s += "<rect class=\"die\" x=\"120\" y=\"120\" width=\"160\" height=\"160\" rx=\"14\"/>\n";
    s += "<rect class=\"die-inner\" x=\"134\" y=\"134\" width=\"132\" height=\"132\" rx=\"8\"/>\n";
    s += "<circle cx=\"142\" cy=\"142\" r=\"4\" fill=\"#f2c66d\"/>\n";   // pin 1 mark
    s += "<text class=\"die-text\" x=\"200\" y=\"210\">EEE</text>\n";
    s += "<text class=\"die-sub\" x=\"200\" y=\"236\">RTL  to  Silicon</text>\n";
    s += "</g>\n</svg>\n";
    return s;
}

// ---------- big "contact me" box at the bottom of the pages ----------
string ctaHtml() {
    string s = "<section class=\"wrap\">\n<div class=\"cta reveal\">\n";
    s += "<h2>Let's work and learn together</h2>\n";
    s += "<p>Have a project, an idea or a question about electronics and chip design? I would love to hear from you.</p>\n";
    s += "<div class=\"btn-row\"><a class=\"btn primary\" href=\"contact.html\">Contact me</a>";
    s += "<a class=\"btn\" href=\"" + assetUrl(CV_FILE) + "\" download>Download CV</a></div>\n";
    s += "</div>\n</section>\n";
    return s;
}

// (the footer is in its own file: footer.h)

// ---------- keyframes for the changing words on the home page ----------
// The number of words comes from data.h, so you can add or remove words freely.
// Each word is visible for its own share of the total time.
string rotatorCss() {
    int n = (int)typingWords.size();
    double share = 100.0 / n;
    string s = "\n@keyframes wordShow{\n";
    s += "0%{opacity:0;transform:translateY(10px)}\n";
    s += to_string(share * 0.1) + "%{opacity:1;transform:none}\n";
    s += to_string(share * 0.85) + "%{opacity:1;transform:none}\n";
    s += to_string(share) + "%{opacity:0;transform:translateY(-10px)}\n";
    s += "100%{opacity:0}\n}\n";
    return s;
}
