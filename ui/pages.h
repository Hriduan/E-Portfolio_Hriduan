// =====================================================
//  pages.h  -  ONE FUNCTION FOR EACH NORMAL PAGE
//  Home, About, Experience and Contact.
//  (the Projects page and the project pages are in
//   projects/project_pages.h)
//  Every function returns the full text of one page.
// =====================================================
#pragma once
#include <string>
#include "site_data.h"
#include "layout.h"
#include "footer.h"
#include "../projects/project_pages.h"
using namespace std;

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

    // chip + numbers ({projects} becomes the real number of projects)
    s += "<section class=\"wrap\">\n<div class=\"chip-panel reveal\">\n";
    s += "<div class=\"chip-view\"><span class=\"chip-label\">Semiconductor chip</span>" + chipSvg() + "</div>\n";
    s += "<div class=\"chip-stats\">\n";
    for (int i = 0; i < (int)stats.size(); i++) {
        string value = replaceAll(stats[i].value, "{projects}", to_string(projects.size()));
        string label = replaceAll(stats[i].label, "{projects}", to_string(projects.size()));
        s += "<div class=\"stat\"><b>" + value + "</b><span>" + label + "</span></div>\n";
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
    s += "<div class=\"reveal\">";
    for (int i = 0; i < (int)aboutParagraphs.size(); i++) {
        s += "<p>" + aboutParagraphs[i] + "</p>";
    }
    s += "<div class=\"tags\"><span class=\"tag\">" + LOCATION + "</span><span class=\"tag\">" + UNI_SHORT + "</span><span class=\"tag\">" + FIELD_SHORT + "</span></div></div>\n";
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
// The form is sent by the free FormSubmit service (no JavaScript needed).
// It delivers a clean, tidy email (a table with name, email, subject, message)
// to the email address from about-me.txt.
// One time only: after the very first test message, FormSubmit sends an
// "Activate" email to that address. Click the button in it. (See README.md)
string contactPage() {
    string s = startPage("Contact", "contact.html");
    s += pageTitle("Contact me", "Send me a message, or find me on LinkedIn. You can also download my CV here.");

    s += "<section class=\"wrap section\">\n<div class=\"contact\">\n<div class=\"reveal\">\n";
    s += "<a class=\"info-link\" href=\"mailto:" + EMAIL + "\"><span class=\"ico\">@</span><span><small>Email</small><strong>" + EMAIL + "</strong></span></a>\n";
    s += "<a class=\"info-link\" href=\"tel:" + telHref() + "\"><span class=\"ico\">Ph</span><span><small>Phone</small><strong>" + PHONE + "</strong></span></a>\n";
    s += "<a class=\"info-link\" href=\"" + LINKEDIN + "\" target=\"_blank\" rel=\"noopener\"><span class=\"ico\">in</span><span><small>LinkedIn</small><strong>" + FULL_NAME + "</strong></span></a>\n";
    s += "<div class=\"info-link\"><span class=\"ico\">Loc</span><span><small>Location</small><strong>" + LOCATION + "</strong></span></div>\n";
    s += "<div class=\"card cv-card\"><h3>My CV</h3><p>Get my full CV as a PDF file.</p>";
    s += "<a class=\"btn primary\" href=\"" + assetUrl(CV_FILE) + "\" download>Download CV</a></div>\n";
    s += "</div>\n";

    s += "<form class=\"card reveal\" action=\"https://formsubmit.co/" + EMAIL + "\" method=\"POST\">\n";
    s += "<div class=\"sent-note\" id=\"sent\"><strong>Thank you!</strong> Your message was sent. I will reply to your email soon.</div>\n";
    s += "<input type=\"hidden\" name=\"_subject\" value=\"New message from your portfolio website\">\n";
    s += "<input type=\"hidden\" name=\"_template\" value=\"table\">\n";
    s += "<input type=\"hidden\" name=\"_captcha\" value=\"false\">\n";
    if (!SITE_URL.empty()) {
        s += "<input type=\"hidden\" name=\"_next\" value=\"" + SITE_URL + "/contact.html#sent\">\n";
    }
    s += "<input class=\"hp\" type=\"text\" name=\"_honey\" tabindex=\"-1\" autocomplete=\"off\" aria-hidden=\"true\">\n";   // spam trap: people never see it
    s += "<label for=\"cName\">Your name</label><input id=\"cName\" name=\"Name\" type=\"text\" autocomplete=\"name\" required>\n";
    s += "<label for=\"cEmail\">Your email</label><input id=\"cEmail\" name=\"email\" type=\"email\" autocomplete=\"email\" required>\n";
    s += "<label for=\"cSubject\">Subject</label><input id=\"cSubject\" name=\"Subject\" type=\"text\" required>\n";
    s += "<label for=\"cMessage\">Message</label><textarea id=\"cMessage\" name=\"Message\" required></textarea>\n";
    s += "<button class=\"btn primary\" type=\"submit\">Send message</button>\n";
    s += "<p class=\"form-note\">Your message goes straight to my inbox. Prefer your own email app? <a href=\"mailto:" + EMAIL + "?subject=Message%20from%20your%20portfolio\">Write me an email</a>.</p>\n</form>\n";
    s += "</div>\n</section>\n";

    s += footerHtml();
    return s;
}
