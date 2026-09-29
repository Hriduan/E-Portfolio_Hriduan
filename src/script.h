// =====================================================
//  script.h  -  ALL THE EFFECTS (JavaScript) ARE HERE
//  Every effect is a small function with a comment.
//  The browser needs this file to run animations.
// =====================================================
#pragma once
#include <string>
using namespace std;

const string JS_TEXT = R"JS(
// ---------- 1. Welcome loading animation ----------
function startLoader() {
  var loader = document.getElementById("loader");
  if (!loader) return;

  // the small script in <head> adds class "seen" if it already played in this visit
  if (document.documentElement.className.indexOf("seen") !== -1) return;

  var bar = document.getElementById("loaderBar");
  var percent = document.getElementById("loaderPercent");
  var n = 0;
  document.body.classList.add("locked");

  var timer = setInterval(function () {
    n = n + 2;
    bar.style.width = n + "%";
    percent.textContent = n + "%";
    if (n >= 100) {
      clearInterval(timer);
      try { sessionStorage.setItem("seenLoader", "yes"); } catch (e) {}
      setTimeout(function () {
        loader.classList.add("hide");
        document.body.classList.remove("locked");
      }, 250);
    }
  }, 30);
}

// ---------- 2. Mobile menu button ----------
function setupMenu() {
  var btn = document.getElementById("menuBtn");
  var menu = document.getElementById("menu");
  if (!btn) return;
  btn.addEventListener("click", function () {
    btn.classList.toggle("open");
    menu.classList.toggle("open");
  });
}

// ---------- 3. Scroll bar on top + navbar shadow + back to top ----------
function setupScroll() {
  var progress = document.getElementById("progress");
  var nav = document.querySelector(".nav");
  window.addEventListener("scroll", function () {
    var max = document.documentElement.scrollHeight - window.innerHeight;
    var percent = max > 0 ? (window.scrollY / max) * 100 : 0;
    progress.style.width = percent + "%";
    if (window.scrollY > 20) nav.classList.add("scrolled");
    else nav.classList.remove("scrolled");
  });
  var topBtn = document.getElementById("toTop");
  if (topBtn) {
    topBtn.addEventListener("click", function () {
      window.scrollTo({ top: 0, behavior: "smooth" });
    });
  }
}

// ---------- 4. Show elements slowly when they come on screen ----------
function setupReveal() {
  var items = document.querySelectorAll(".reveal");
  if (!("IntersectionObserver" in window)) {
    items.forEach(function (el) { el.classList.add("show"); });
    return;
  }
  var watcher = new IntersectionObserver(function (entries) {
    entries.forEach(function (entry) {
      if (entry.isIntersecting) {
        entry.target.classList.add("show");
        watcher.unobserve(entry.target);
      }
    });
  }, { threshold: 0.12 });
  items.forEach(function (el, i) {
    el.style.transitionDelay = (i % 4) * 0.08 + "s";
    watcher.observe(el);
  });
}

// ---------- 5. Typing text on the home page ----------
function setupTyping() {
  var box = document.getElementById("typing");
  if (!box) return;
  var words = box.getAttribute("data-words").split("|");
  var wordNo = 0;
  var letterNo = 0;
  var deleting = false;

  function type() {
    var word = words[wordNo];
    if (deleting) letterNo--;
    else letterNo++;
    box.textContent = word.substring(0, letterNo);

    var wait = deleting ? 35 : 70;
    if (!deleting && letterNo === word.length) { deleting = true; wait = 1600; }
    else if (deleting && letterNo === 0) { deleting = false; wordNo = (wordNo + 1) % words.length; wait = 400; }
    setTimeout(type, wait);
  }
  type();
}

// ---------- 6. Numbers counting up ----------
function setupCounters() {
  var counters = document.querySelectorAll(".count");
  if (counters.length === 0) return;

  var watcher = new IntersectionObserver(function (entries) {
    entries.forEach(function (entry) {
      if (!entry.isIntersecting) return;
      var el = entry.target;
      var text = el.getAttribute("data-value");
      var target = parseFloat(text);
      var decimals = text.indexOf(".") !== -1 ? text.split(".")[1].length : 0;
      var current = 0;
      var step = target / 40;
      var timer = setInterval(function () {
        current = current + step;
        if (current >= target) { current = target; clearInterval(timer); }
        el.textContent = current.toFixed(decimals);
      }, 30);
      watcher.unobserve(el);
    });
  }, { threshold: 0.5 });
  counters.forEach(function (c) { watcher.observe(c); });
}

// ---------- 7. Glow that follows the mouse + card tilt (desktop only) ----------
function setupMouseEffects() {
  if (!window.matchMedia("(hover: hover)").matches) return;

  var glow = document.getElementById("glow");
  document.addEventListener("mousemove", function (e) {
    glow.style.left = e.clientX + "px";
    glow.style.top = e.clientY + "px";
  });

  document.querySelectorAll(".tilt").forEach(function (card) {
    card.addEventListener("mousemove", function (e) {
      var box = card.getBoundingClientRect();
      var x = (e.clientX - box.left) / box.width - 0.5;
      var y = (e.clientY - box.top) / box.height - 0.5;
      card.style.transform = "perspective(800px) rotateY(" + x * 7 + "deg) rotateX(" + (-y * 7) + "deg) translateY(-6px)";
    });
    card.addEventListener("mouseleave", function () {
      card.style.transform = "";
    });
  });
}

// ---------- 8. Smooth fade when opening another page ----------
function setupPageFade() {
  document.querySelectorAll("a").forEach(function (link) {
    var href = link.getAttribute("href");
    if (!href || href.indexOf(".html") === -1 || href.indexOf("http") === 0) return;
    link.addEventListener("click", function (e) {
      if (e.ctrlKey || e.metaKey || e.shiftKey) return;
      e.preventDefault();
      document.body.classList.add("leaving");
      setTimeout(function () { window.location.href = href; }, 250);
    });
  });
  // when user presses the browser back button
  window.addEventListener("pageshow", function () {
    document.body.classList.remove("leaving");
  });
}

// ---------- 9. Click on a project photo to see it big ----------
function setupLightbox() {
  var photos = document.querySelectorAll(".gallery figure");
  if (photos.length === 0) return;

  var box = document.createElement("div");
  box.id = "lightbox";
  box.innerHTML = "<div><img id='bigImg' alt=''><p id='bigCaption'></p></div>";
  document.body.appendChild(box);

  photos.forEach(function (fig) {
    fig.addEventListener("click", function () {
      document.getElementById("bigImg").src = fig.querySelector("img").src;
      document.getElementById("bigCaption").textContent = fig.querySelector("figcaption").textContent;
      box.classList.add("open");
    });
  });
  box.addEventListener("click", function () { box.classList.remove("open"); });
  document.addEventListener("keydown", function (e) {
    if (e.key === "Escape") box.classList.remove("open");
  });
}

// ---------- 10. Contact form opens the email app ----------
function setupContactForm() {
  var form = document.getElementById("contactForm");
  if (!form) return;
  form.addEventListener("submit", function (e) {
    e.preventDefault();
    var name = document.getElementById("cName").value;
    var subject = document.getElementById("cSubject").value;
    var message = document.getElementById("cMessage").value;
    var body = message + "\n\nFrom: " + name;
    window.location.href = "mailto:" + form.getAttribute("data-email") +
      "?subject=" + encodeURIComponent(subject) + "&body=" + encodeURIComponent(body);
  });
}

// ---------- run everything ----------
startLoader();
setupMenu();
setupScroll();
setupReveal();
setupTyping();
setupCounters();
setupMouseEffects();
setupPageFade();
setupLightbox();
setupContactForm();
)JS";
