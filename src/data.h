// =====================================================
//  data.h  -  ALL THE CONTENT OF THE WEBSITE IS HERE
//  To change any text, project, skill or link, edit this
//  file only, then build again (see README.md).
// =====================================================
#pragma once
#include <string>
#include <vector>
using namespace std;

// ---------- 1. BASIC INFO ----------
const string SITE_NAME  = "Siam";
const string FULL_NAME  = "Hriduan Omor Siam";
const string ROLE       = "Electrical & Electronic Engineering student";
const string TAGLINE    = "I love building practical electronics projects that solve real-world problems.";
const string BADGE      = "Final-year EEE, AIUB";
const string EMAIL      = "hriduansiam101@gmail.com";
const string PHONE      = "+880 140 072 9346";
const string LINKEDIN   = "https://www.linkedin.com/in/hriduan-omor-siam-27870b363";
const string LOCATION   = "Dhaka, Bangladesh";
const string UNIVERSITY = "American International University-Bangladesh (AIUB)";
const string YEAR       = "2026";

// ONE folder holds every image and the CV (profile photo, project photos, demo image, CV)
const string ASSETS_DIR = "assets";

// file names inside the assets folder
const string PROFILE_PHOTO = "profile.jpg";
const string CV_FILE       = "Hriduan_CV.pdf";
const string DEMO_IMAGE    = "demo.jpg";

// web address of a file inside the assets folder, e.g. assetUrl("profile.jpg") -> "assets/profile.jpg"
inline string assetUrl(const string& file) { return ASSETS_DIR + "/" + file; }

// words that change by themselves on the home page (add or remove freely)
const vector<string> typingWords = {
    "Electrical & Electronic Engineering student",
    "Chip design enthusiast",
    "RTL verification learner",
    "Electronics project builder"
};

// ---------- 2. ABOUT ME ----------
const string ABOUT_1 = "I am a final-year Electrical and Electronic Engineering student with a deep passion for electronics and automation. I love getting my hands dirty building practical projects that actually solve real-world problems.";
const string ABOUT_2 = "Whether it is designing a smart farming system or organizing student events, I always put my heart into what I do and try to learn something new every day.";

// ---------- 3. NUMBERS ON THE HOME PAGE ----------
struct Stat {
    string value;   // the number (can have a dot)
    string label;   // small text under it
};
const vector<Stat> stats = {
    {"3.87", "CGPA at AIUB"},
    {"5",    "hands-on projects"},
    {"2",    "team leader roles"}
};

// ---------- 4. INTERESTS ----------
struct Interest {
    string name;
    string text;
};
const vector<Interest> interests = {
    {"Semiconductor",  "How tiny devices made of silicon run the modern world."},
    {"Chip Design",    "Turning an idea into a working digital chip."},
    {"RTL Verification", "Checking that the chip design behaves exactly as planned."},
    {"PnR",            "Place and route: giving the design a real layout on silicon."},
    {"PV Cells",       "Photovoltaic cells that turn sunlight into electricity."},
    {"Nanotechnology", "Working with materials at a very tiny scale."},
    {"Perovskites",    "A fast-growing material for next generation solar cells."}
};

// ---------- 5. PROJECTS ----------
// every project has 4 images. Put your real photo in
// the assets folder with the SAME file name and it will replace the demo image.
struct Photo {
    string file;      // image file name
    string caption;   // text shown under the image
};

struct Project {
    string slug;                // used in the page name: project-<slug>.html
    string title;
    string category;
    string summary;             // short text on the project tile
    vector<string> details;     // paragraphs on the project page
    vector<string> features;    // bullet list on the project page
    vector<string> tools;       // small tags on the project page
    vector<Photo> photos;       // first photo is used on the tile
};

const vector<Project> projects = {
    {
        "digital-voting-machine",
        "Digital Voting Machine",
        "Embedded system",
        "An electronic voting system that scans NID cards to automatically verify voters.",
        {
            "I built this project because I wanted to make the voting process more secure and reliable. Before a person can vote, the machine scans their NID card and checks the voter automatically.",
            "The idea is simple: verify first, then allow the vote. This way the system does not depend on manual checking."
        },
        {"Scans NID cards", "Automatic voter verification", "Made for a secure and reliable voting process"},
        {"Electronics", "Microcontroller", "NID card scanning"},
        {
            {"voting-machine-main.jpg",    "Main setup of the voting machine"},
            {"voting-machine-scanner.jpg", "NID card scanning part"},
            {"voting-machine-circuit.jpg", "Circuit and connections"},
            {"voting-machine-testing.jpg", "Testing the final system"}
        }
    },
    {
        "smart-agriculture-model",
        "Smart Agriculture Model",
        "Automation",
        "A smart farm prototype with automatic irrigation, a food dispenser and a secure RFID entrance.",
        {
            "I designed and put together this smart farm prototype to show how automation can make farming easier.",
            "It has three main parts: an automatic irrigation setup, a food dispenser, and an RFID card system that keeps the farm entrance secure."
        },
        {"Automatic irrigation setup", "Food dispenser", "RFID card system for the farm entrance"},
        {"Automation", "RFID", "Microcontroller"},
        {
            {"smart-farm-model.jpg",      "The complete smart farm model"},
            {"smart-farm-irrigation.jpg", "Automatic irrigation part"},
            {"smart-farm-dispenser.jpg",  "Food dispenser part"},
            {"smart-farm-rfid-gate.jpg",  "RFID card entrance"}
        }
    },
    {
        "solar-street-light",
        "Solar Street Light & Phone Charger",
        "Renewable energy",
        "A solar-powered street light that also works as a mobile phone charging station.",
        {
            "For this project I used basic components like diodes and op-amps to create a functional street light powered by solar energy.",
            "The same setup also works as a convenient charging station for mobile phones."
        },
        {"Powered by solar energy", "Street light built with diodes and op-amps", "Mobile phone charging point"},
        {"Solar energy", "Diodes", "Op-amps"},
        {
            {"solar-light-main.jpg",    "Solar street light prototype"},
            {"solar-light-panel.jpg",   "Solar panel side"},
            {"solar-light-circuit.jpg", "Diode and op-amp circuit"},
            {"solar-light-charger.jpg", "Phone charging point"}
        }
    },
    {
        "ultrasound-sonar-rfid",
        "Ultrasound Sonar & RFID Access",
        "Arduino",
        "An Arduino based ultrasound sonar system combined with an RFID access and control mechanism.",
        {
            "In this project I developed an ultrasound sonar system using Arduino.",
            "I also connected it with an RFID access and control mechanism, so the same system can measure distance and control who gets access."
        },
        {"Ultrasound sonar built with Arduino", "RFID access and control", "Both parts working in one system"},
        {"Arduino", "Ultrasonic sensor", "RFID"},
        {
            {"sonar-rfid-main.jpg",       "Sonar and RFID system"},
            {"sonar-arduino-board.jpg",   "Arduino board setup"},
            {"sonar-ultrasonic-test.jpg", "Ultrasonic sensor test"},
            {"sonar-rfid-access.jpg",     "RFID access control part"}
        }
    },
    {
        "audio-signal-filtering",
        "Audio Signal Filtering",
        "Signal processing",
        "Bandpass and low pass filters designed in MATLAB to process and filter audio signals.",
        {
            "This project is about processing audio signals. I designed bandpass and low pass filters using MATLAB and used them to filter the audio.",
            "It helped me understand how filters work on real signals and not only on paper."
        },
        {"Bandpass filter design", "Low pass filter design", "Audio signal processing in MATLAB"},
        {"MATLAB", "Filter design", "Signal processing"},
        {
            {"audio-filter-main.jpg",     "Audio filtering project"},
            {"audio-filter-bandpass.jpg", "Bandpass filter result"},
            {"audio-filter-lowpass.jpg",  "Low pass filter result"},
            {"audio-filter-matlab.jpg",   "MATLAB code and output"}
        }
    }
};

// ---------- 6. EDUCATION ----------
struct Education {
    string school;
    string degree;
    string place;
    string result;
    string year;
};
const vector<Education> education = {
    {"American International University-Bangladesh (AIUB)", "BSc in Electrical and Electronic Engineering (EEE)", "Dhaka, Bangladesh", "CGPA: 3.87 (9th semester completed)", "Present"},
    {"Mymensingh Polytechnic Institute", "Diploma in Electronics Engineering", "Mymensingh, Bangladesh", "CGPA: 3.18", "2023"},
    {"Saint Andrews's High School", "Secondary School Certificate (Science)", "Haluaghat, Mymensingh", "GPA: 4.55", "2017"}
};

// ---------- 7. LEADERSHIP & EXPERIENCE ----------
struct Experience {
    string tag;
    string title;
    string text;
};
const vector<Experience> experiences = {
    {"Leadership", "Hostel Leader", "During my diploma, my teachers selected me to handle all the daily operations in the hostel. I took care of daily management and organized several events to keep our student community active and engaged."},
    {"Competition", "VLSITHON 3.0 Participant", "Participated in VLSITHON 3.0 as a group leader. The event was organized by Ulkasemi."},
    {"Competition", "Poster Presentation Participant", "Participated in the poster presentation competition as an author, organized by the Bangladesh Youth Nuclear Congress (BYNC), as part of I4N x INNOVENTURE Bangladesh 2026."},
    {"Event", "Semiconductor Symposium Attendee", "Attended the National Semiconductor Symposium & BEAR Summit 2026."},
    {"Visit", "Industrial Tour", "Attended an industrial tour to PGCB (Power Grid Company of Bangladesh), organized by my university."},
    {"Learning", "Continuous Learner", "I regularly attend engineering seminars at my university to keep up with the latest industry trends and learn beyond my regular classroom syllabus."}
};

// ---------- 8. SKILLS ----------
struct SkillGroup {
    string title;
    vector<string> items;
};
const vector<SkillGroup> skills = {
    {"Technical Skills",   {"Circuit design", "Microcontrollers", "RFID", "Electronics engineering", "Solar energy setups"}},
    {"Programming Skills", {"C/C++ (Intermediate)", "MATLAB (Intermediate)", "System Verilog (Intermediate)"}},
    {"Simulation Skills",  {"Multisim", "Cadence Virtuoso", "Cadence Genus", "Cadence Innovus", "RealVNC"}},
    {"Soft Skills",        {"Paperwork and documentation", "Organizing events", "Leading teams", "Communication"}}
};
