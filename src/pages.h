// =====================================================
//  pages.h  -  ONE FUNCTION FOR EACH PAGE
//  Every function returns the full text of one page.
// =====================================================
#pragma once
#include <string>
#include "data.h"
#include "layout.h"
#include "footer.h"
using namespace std;

// small helper: start and end of a normal page
string startPage(const string& title, const string& file) {
    // the welcome loading screen is shown on the home page only
    string loader = (file == "index.html") ? loaderHtml() : "";
    return pageHead(title) + loader + navHtml(file);
}

// small helper: title box at top of inner pages
string pageTitle(const string& title, const string& text) {
    return "<section class=\"wrap page-hero\">\n<h1>" + title + "</h1>\n<p>" + text + "</p>\n</section>\n";
}

// one project tile (used on home and projects page)
string projectTile(const Project& p) {
    string s = "<a class=\"tile reveal\" href=\"project-" + p.slug + ".html\">\n";
    s += "<div class=\"tile-img\"><img src=\"" + assetUrl(p.photos[0].file) + "\" alt=\"" + p.title + "\" loading=\"lazy\">";
    s += "<span class=\"tile-cat\">" + p.category + "</span></div>\n";
    s += "<div class=\"tile-body\"><h3>" + p.title + "</h3><p>" + p.summary + "</p>";
    s += "<span class=\"more\">View details <b>&rarr;</b></span></div>\n</a>\n";
    return s;
}

// ---------------------- HOME PAGE ----------------------
string homePage() {
    string s = startPage("Home", "index.html");

    // hero
    s += "<section class=\"wrap hero\">\n<div>\n";
    s += "<p class=\"hero-hi\">Hello, I am</p>\n";
    s += "<h1>" + FULL_NAME + "</h1>\n";
    s += "<p class=\"hero-role\"><span class=\"rotator\" style=\"--total:" + to_string(typingWords.size() * 3) + "s\">";
    for (int i = 0; i < (int)typingWords.size(); i++) {
        s += "<span style=\"animation-delay:" + to_string(i * 3) + "s\">" + typingWords[i] + "</span>";
    }
    s += "</span></p>\n";
    s += "<p class=\"hero-text\">" + TAGLINE + "</p>\n";
    s += "<div class=\"btn-row\"><a class=\"btn primary\" href=\"projects.html\">See my projects</a>";
    s += "<a class=\"btn\" href=\"" + assetUrl(CV_FILE) + "\" download>Download CV</a></div>\n</div>\n";
    s += "<div class=\"photo-wrap\"><div class=\"photo-frame\"><img src=\"" + assetUrl(PROFILE_PHOTO) + "\" alt=\"" + FULL_NAME + "\"></div>";
    s += "<div class=\"photo-badge\">" + BADGE + "</div></div>\n</section>\n";

    // chip + numbers
    s += "<section class=\"wrap\">\n<div class=\"chip-panel reveal\">\n";
    s += "<div class=\"chip-view\"><span class=\"chip-label\">Semiconductor chip</span>" + chipSvg() + "</div>\n";
    s += "<div class=\"chip-stats\">\n";
    for (int i = 0; i < (int)stats.size(); i++) {
        s += "<div class=\"stat\"><b>" + stats[i].value + "</b><span>" + stats[i].label + "</span></div>\n";
    }
    s += "</div>\n</div>\n</section>\n";

    // interests strip (list is written two times so the scroll never has a gap)
    s += "<section class=\"section\">\n<div class=\"wrap\"><div class=\"section-head reveal\"><h2>What I am interested in</h2>";
    s += "<p>The topics I read about, practice and want to build my career on.</p></div></div>\n";
    s += "<div class=\"marquee\"><div class=\"marquee-track\">\n";
    for (int round = 0; round < 2; round++) {
        for (int i = 0; i < (int)interests.size(); i++) {
            s += "<span>" + interests[i].name + "</span>";
        }
    }
    s += "\n</div></div>\n</section>\n";

    // featured projects (first three)
    s += "<section class=\"wrap\">\n<div class=\"section-head reveal\"><h2>Featured projects</h2>";
    s += "<p>Click any project to see the photos and full details.</p></div>\n<div class=\"projects-grid\">\n";
    for (int i = 0; i < 3 && i < (int)projects.size(); i++) {
        s += projectTile(projects[i]);
    }
    s += "</div>\n<div class=\"btn-row\"><a class=\"btn\" href=\"projects.html\">View all projects</a></div>\n</section>\n";

    s += "<div class=\"section\">\n" + ctaHtml() + "</div>\n";
    s += footerHtml();
    return s;
}

// ---------------------- ABOUT PAGE ----------------------
string aboutPage() {
    string s = startPage("About", "about.html");
    s += pageTitle("About me", "A short story about who I am, where I study and what I love to learn.");

    // about text + photo
    s += "<section class=\"wrap section\">\n<div class=\"about\">\n";
    s += "<div class=\"photo-wrap reveal\"><div class=\"photo-frame\"><img src=\"" + assetUrl(PROFILE_PHOTO) + "\" alt=\"" + FULL_NAME + "\"></div></div>\n";
    s += "<div class=\"reveal\"><p>" + ABOUT_1 + "</p><p>" + ABOUT_2 + "</p>";
    s += "<div class=\"tags\"><span class=\"tag\">" + LOCATION + "</span><span class=\"tag\">AIUB</span><span class=\"tag\">EEE</span></div></div>\n";
    s += "</div>\n</section>\n";

    // interests
    s += "<section class=\"wrap\">\n<div class=\"section-head reveal\"><h2>My interests</h2><p>Where I want to grow in the future.</p></div>\n<div class=\"grid\">\n";
    for (int i = 0; i < (int)interests.size(); i++) {
        s += "<div class=\"card interest reveal\"><span class=\"dot\"></span><h3>" + interests[i].name + "</h3><p>" + interests[i].text + "</p></div>\n";
    }
    s += "</div>\n</section>\n";

    // education
    s += "<section class=\"wrap section\">\n<div class=\"section-head reveal\"><h2>Education</h2><p>My study journey so far.</p></div>\n<div class=\"timeline\">\n";
    for (int i = 0; i < (int)education.size(); i++) {
        const Education& e = education[i];
        s += "<div class=\"card t-item reveal\"><small>" + e.year + "</small><h3>" + e.school + "</h3>";
        s += "<p>" + e.degree + "</p><p>" + e.place + "</p><span class=\"tag\">" + e.result + "</span></div>\n";
    }
    s += "</div>\n</section>\n";

    s += ctaHtml();
    s += footerHtml();
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
// i = number of the project in the list in data.h
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

    // previous and next project
    int total = (int)projects.size();
    int prev = (i + total - 1) % total;
    int next = (i + 1) % total;
    s += "<div class=\"pager\">\n";
    s += "<a href=\"project-" + projects[prev].slug + ".html\"><small>&larr; Previous project</small>" + projects[prev].title + "</a>\n";
    s += "<a class=\"next\" href=\"project-" + projects[next].slug + ".html\"><small>Next project &rarr;</small>" + projects[next].title + "</a>\n";
    s += "</div>\n</section>\n";

    s += footerHtml();
    return s;
}

// ---------------------- EXPERIENCE PAGE ----------------------
string experiencePage() {
    string s = startPage("Experience", "experience.html");
    s += pageTitle("Leadership & experience", "Events, competitions and roles that helped me grow outside the classroom.");

    s += "<section class=\"wrap section\">\n<div class=\"timeline\">\n";
    for (int i = 0; i < (int)experiences.size(); i++) {
        s += "<div class=\"card t-item reveal\"><span class=\"tag\">" + experiences[i].tag + "</span><h3>" + experiences[i].title + "</h3><p>" + experiences[i].text + "</p></div>\n";
    }
    s += "</div>\n</section>\n";

    s += "<section class=\"wrap\">\n<div class=\"section-head reveal\"><h2>Skills</h2><p>The tools and abilities I use in my projects.</p></div>\n<div class=\"grid\">\n";
    for (int i = 0; i < (int)skills.size(); i++) {
        s += "<div class=\"card skill-card reveal\"><h3>" + skills[i].title + "</h3><div class=\"tags\">";
        for (int k = 0; k < (int)skills[i].items.size(); k++) {
            s += "<span class=\"tag\">" + skills[i].items[k] + "</span>";
        }
        s += "</div></div>\n";
    }
    s += "</div>\n</section>\n";

    s += "<div class=\"section\">\n" + ctaHtml() + "</div>\n";
    s += footerHtml();
    return s;
}

// ---------------------- CONTACT PAGE ----------------------
string contactPage() {
    string s = startPage("Contact", "contact.html");
    s += pageTitle("Contact me", "Send me a message, or find me on LinkedIn. You can also download my CV here.");

    s += "<section class=\"wrap section\">\n<div class=\"contact\">\n<div class=\"reveal\">\n";
    s += "<a class=\"info-link\" href=\"mailto:" + EMAIL + "\"><span class=\"ico\">@</span><span><small>Email</small><strong>" + EMAIL + "</strong></span></a>\n";
    s += "<a class=\"info-link\" href=\"tel:" + PHONE + "\"><span class=\"ico\">Ph</span><span><small>Phone</small><strong>" + PHONE + "</strong></span></a>\n";
    s += "<a class=\"info-link\" href=\"" + LINKEDIN + "\" target=\"_blank\" rel=\"noopener\"><span class=\"ico\">in</span><span><small>LinkedIn</small><strong>Hriduan Omor Siam</strong></span></a>\n";
    s += "<div class=\"info-link\"><span class=\"ico\">Loc</span><span><small>Location</small><strong>" + LOCATION + "</strong></span></div>\n";
    s += "<div class=\"card cv-card\"><h3>My CV</h3><p>Get my full CV as a PDF file.</p>";
    s += "<a class=\"btn primary\" href=\"" + assetUrl(CV_FILE) + "\" download>Download CV</a></div>\n";
    s += "</div>\n";

    s += "<form class=\"card reveal\" action=\"mailto:" + EMAIL + "?subject=Message%20from%20your%20portfolio\" method=\"post\" enctype=\"text/plain\">\n";
    s += "<label for=\"cName\">Your name</label><input id=\"cName\" name=\"Name\" type=\"text\" required>\n";
    s += "<label for=\"cSubject\">Subject</label><input id=\"cSubject\" name=\"Subject\" type=\"text\" required>\n";
    s += "<label for=\"cMessage\">Message</label><textarea id=\"cMessage\" name=\"Message\" required></textarea>\n";
    s += "<button class=\"btn primary\" type=\"submit\">Send message</button>\n";
    s += "<p style=\"margin-top:14px\">This opens your email app with the message ready to send.</p>\n</form>\n";
    s += "</div>\n</section>\n";

    s += footerHtml();
    return s;
}
