var classnum = window.location.pathname.match(/cisc\/(\d+)/)[1];
var topicNum = +(window.location.pathname.split("/").slice(-2, -1)[0].split("_")[1]);
var prevTopic = ((topicNum - 1 < 10) ? "0" : "") + (topicNum - 1);
var nextTopic = ((topicNum + 1 < 10) ? "0" : "") + (topicNum + 1);
var pageNum = +(window.location.pathname.split("/").pop().split('.')[0]);
var prevPage = ((pageNum - 1 < 10) ? "0" : "") + (pageNum - 1);
var nextPage = ((pageNum + 1 < 10) ? "0" : "") + (pageNum + 1);

var pageMode = localStorage.getItem("modeLec");
if (pageMode != "light" && pageMode != "dark")
    localStorage.setItem("modeLec", "light");
var pageMode = localStorage.getItem("modeLec");
if (pageMode == "light")
    document.getElementById("darkstyle").disabled = true;
else if (pageMode == "dark")
    document.getElementById("lightstyle").disabled = true;

window.addEventListener('DOMContentLoaded', function() {
    if (typeof MathJax !== 'undefined') {
        MathJax.Hub.Config({
            menuSettings: {
              inTabOrder: false
            }
        });
    }
});

let touchStartX = 0;
let touchEndX = 0;
const SWIPE_THRESHOLD = 50;

// Attach directly to window to listen across the entire screen
window.addEventListener('touchstart', (e) => {
  if (e.touches.length === 2) {
    touchStartX = (e.touches[0].clientX + e.touches[1].clientX) / 2;
  }
}, { passive: true });

window.addEventListener('touchend', (e) => {
  // Check the total number of involved touches
  const totalTouches = e.touches.length + e.changedTouches.length;
  
  if (totalTouches === 2 && e.changedTouches.length >= 1) {
    // Safely grab coordinates from either touches still on screen or touches that just left
    const finger1 = e.changedTouches[0] || e.touches[0];
    const finger2 = e.changedTouches[1] || e.touches[0]; // Fallback to first if only one left
    
    touchEndX = (finger1.clientX + finger2.clientX) / 2;
    handleTwoFingerSwipe();
  }
});

function handleTwoFingerSwipe() {
  const swipeDistance = touchEndX - touchStartX;

  if (Math.abs(swipeDistance) > SWIPE_THRESHOLD) {
    if (swipeDistance > 0)
    {
        if (prevPage !== "00" && prevPage !== "0" && prevPage !== "NaN")
        {
            window.location.href = "./" + prevPage + ".html";
        }
        else
        {
            if (localStorage.getItem(classnum + "_topic_" + (topicNum - 1)) !== null)
            {
                fetch("../topic_" + prevTopic + "/" + localStorage.getItem(classnum + "_topic_" + (topicNum - 1)) + ".html", { method: 'HEAD' })
                    .then(response => {
                          if (response.ok)
                              window.location.href = "../topic_" + prevTopic + "/" + localStorage.getItem(classnum + "_topic_" + (topicNum - 1)) + ".html";
                })
                .catch(error => {});
            }
            else
            {
                fetch("../topic_" + prevTopic + "/01.html", { method: 'HEAD' })
                    .then(response => {
                          if (response.ok)
                              window.location.href = "../topic_" + prevTopic + "/01.html";
                })
                .catch(error => {});
            }
        }  
    }
    else
    {
        fetch("./" + nextPage + ".html", { method: 'HEAD' })
            .then(response => {
                if (response.ok)
                    window.location.href = "./" + nextPage + ".html";
                else
                {
                    fetch("../topic_" + nextTopic + "/01.html", { method: 'HEAD' })
                        .then(response => {
                            if (response.ok)
                                window.location.href = "../topic_" + nextTopic + "/01.html";
                    })
                    .catch(error => {});
                }
            })
            .catch(error => {});
    }
  }
}

// Pressing <- or -> will move to prev/next slides:
document.addEventListener("keydown", function(event)
{
    if (event.key === "ArrowRight")
    {
        fetch("./" + nextPage + ".html", { method: 'HEAD' })
            .then(response => {
                if (response.ok)
                    window.location.href = "./" + nextPage + ".html";
                else
                {
                    fetch("../topic_" + nextTopic + "/01.html", { method: 'HEAD' })
                        .then(response => {
                            if (response.ok)
                                window.location.href = "../topic_" + nextTopic + "/01.html";
                    })
                    .catch(error => {});
                }
            })
            .catch(error => {});
    }
    else if (event.key === "ArrowLeft" && prevPage !== "00" && prevPage !== "0" && prevPage !== "NaN")
    {
        window.location.href = "./" + prevPage + ".html";
    }
    else if (event.key === "ArrowLeft")
    {
        if (localStorage.getItem(classnum + "_topic_" + (topicNum - 1)) !== null)
        {
            fetch("../topic_" + prevTopic + "/" + localStorage.getItem(classnum + "_topic_" + (topicNum - 1)) + ".html", { method: 'HEAD' })
                .then(response => {
                      if (response.ok)
                          window.location.href = "../topic_" + prevTopic + "/" + localStorage.getItem(classnum + "_topic_" + (topicNum - 1)) + ".html";
            })
            .catch(error => {});
        }
        else
        {
            fetch("../topic_" + prevTopic + "/01.html", { method: 'HEAD' })
                .then(response => {
                      if (response.ok)
                          window.location.href = "../topic_" + prevTopic + "/01.html";
            })
            .catch(error => {});
        }
    }
});

function enumSlide ()
{
    document.getElementsByClassName("pagenum")[0].innerHTML = pageNum;
    document.getElementsByClassName("pagenum")[0].title = "Slide " + pageNum;
}

function navigation ()
{
    if (document.querySelectorAll('.next').length === 2)
    {
        document.getElementsByClassName("next")[0].href = "./" + prevPage + ".html";
        document.getElementsByClassName("next")[1].href = "./" + nextPage + ".html";
    }
    else if (document.querySelectorAll('.next-topic').length === 1)
    {
        document.getElementsByClassName("next-topic")[0].innerText = "Topic " + (topicNum + 1) + " →";
        document.getElementsByClassName("next")[0].href = "./" + prevPage + ".html";
        document.getElementsByClassName("next-topic")[0].href = "../topic_" + nextTopic + "/01.html";
        localStorage.setItem(classnum + "_topic_" + topicNum, (((pageNum < 10) ? "0" : "") + (pageNum)));
    }
    else if (document.querySelectorAll('.prev-topic').length === 1)
    {
        document.getElementsByClassName("prev-topic")[0].innerText = "← " + "Topic " + (topicNum - 1);
        document.getElementsByClassName("next")[0].href = "./" + nextPage + ".html";
        if (localStorage.getItem(classnum + "_topic_" + (topicNum - 1)) !== null)
            document.getElementsByClassName("prev-topic")[0].href = "../topic_" + prevTopic + "/" + localStorage.getItem(classnum + "_topic_" + (topicNum - 1)) + ".html";
        else
            document.getElementsByClassName("prev-topic")[0].href = "../topic_" + prevTopic + "/01.html";
    }
}

function switchFocus (flag)
{
    const element = document.querySelector('#switch-input');

    if (flag == true)
    {
        var pageMode = localStorage.getItem("modeLec");
        if (pageMode == "dark")
            document.getElementById('switch-container').style.border = '2px dashed white';
        else
            document.getElementById('switch-container').style.border = '2px dashed black';
    }
    else
    {
        if (element.matches(':focus-visible'))
        {
            var pageMode = localStorage.getItem("modeLec");
            if (pageMode == "dark")
                document.getElementById('switch-container').style.border = '2px dashed white';
            else
                document.getElementById('switch-container').style.border = '2px dashed black';
        }
    }
}

function switchFocusOut ()
{
    document.getElementById('switch-container').style.border = '2px dashed transparent';
}

function getMode ()
{
    var pageMode = localStorage.getItem("modeLec");
    if (pageMode == "dark")
    {
        document.getElementById("switch-input").checked = true;
        document.getElementById("slider").title = "Change to light/dark mode [dark mode is on]";
    }
    else
    {
        document.getElementById("switch-input").checked = false;
        document.getElementById("slider").title = "Change to light/dark mode [light mode is on]";
    }
}

function switch_work ()
{
    var pageMode = localStorage.getItem("modeLec");
    if (pageMode == "light")
    {
        document.getElementById("darkstyle").disabled = false;
        document.getElementById("lightstyle").disabled = true;
        document.getElementById("slider").title = "Change to light/dark mode [dark mode is on]";
        localStorage.setItem("modeLec", "dark");
    }
    else
    {
        document.getElementById("darkstyle").disabled = true;
        document.getElementById("lightstyle").disabled = false;
        document.getElementById("slider").title = "Change to light/dark mode [light mode is on]";
        localStorage.setItem("modeLec", "light");
    }
}

document.addEventListener(
    "DOMContentLoaded",
    () =>
    {
        SlideNavigator.init();
        SlideNavigator.enableKeyboardControls();
    }
);

window.addEventListener(
    "resize",
    () =>
    {
        SlideNavigator.scalePreview();
    }
);

"use strict";

const SlideNavigator =
{
    HOVER_DELAY: 250,

    TOPIC_NUMBER: null,

    CURRENT_SLIDE: null,

    SLIDE_COUNT: 0,

    MENU: null,

    BUTTON: null,

    POPUP: null,

    FRAME: null,

    HOVER_TIMER: null,

    MENU_VISIBLE: false,

    init()
    {

        this.BUTTON =
            document.getElementById(
                "slideMenuButton"
            );


        this.MENU =
            document.getElementById(
                "slideMenu"
            );


        this.POPUP =
            document.getElementById(
                "slidePreviewPopup"
            );

        if (this.POPUP)
        {
            this.POPUP.tabIndex = -1;

            const previewTitle =
                document.createElement("p");

            previewTitle.id =
                "previewTitle";

            previewTitle.textContent =
                "Hello World!";

            this.POPUP.appendChild(previewTitle);
        }


        this.FRAME =
            document.getElementById(
                "slidePreviewFrame"
            );

        if (this.FRAME)
            this.FRAME.tabIndex = -1;


        if(
            !this.BUTTON ||
            !this.MENU ||
            !this.POPUP ||
            !this.FRAME
        )
        {
            return;
        }


        this.detectCurrentSlide();


        this.BUTTON.addEventListener(
            "click",
            () => this.openMenu()
        );


        this.POPUP.addEventListener(
            "mouseenter",
            () =>
            {
                clearTimeout(
                    this.HOVER_TIMER
                );
            }
        );


        this.POPUP.addEventListener(
            "mouseleave",
            () =>
            {
                this.hidePreview();
            }
        );


        window.addEventListener(
            "load",
            () => this.prepareMenu()
        );

        window.addEventListener(
            "resize",
            () =>
            {

                if(this.POPUP.classList.contains("visible"))
                    this.scalePreview();
            }
        );

    },

    detectCurrentSlide()
    {
        this.TOPIC_NUMBER = topicNum;
        this.CURRENT_SLIDE = pageNum;
    },

    openMenu()
    {

        this.MENU.classList.add(
            "open"
        );


        this.MENU_VISIBLE = true;


        this.scrollToCurrentSlide();

        document.getElementById("switch-input").tabIndex = 2;
        document.getElementById("slideMenuButton").tabIndex = -1;
        document.getElementById("slideMenuClose").tabIndex = 1;
        document.getElementById("slideMenuPDF").tabIndex = 1;
        if (document.getElementById("begin"))
            document.getElementById("begin").tabIndex = 1;
        if (document.getElementById("end"))
            document.getElementById("end").tabIndex = 1;
        if (document.getElementById("PrevTopicButton"))
            document.getElementById("PrevTopicButton").tabIndex = 1;
        if (document.getElementById("NextTopicButton"))
            document.getElementById("NextTopicButton").tabIndex = 1;
        const elements = document.querySelectorAll('.slideEntry');
        for (const element of elements)
            element.tabIndex = 1;
        if (document.getElementsByClassName("current")[0])
            document.getElementsByClassName("current")[0].tabIndex = -1;
    },

    closeMenu()
    {

        this.MENU.classList.remove(
            "open"
        );


        this.MENU_VISIBLE = false;


        this.hidePreview();

        document.getElementById("switch-input").tabIndex = 1;
        document.getElementById("slideMenuButton").tabIndex = 1;
        document.getElementById("slideMenuClose").tabIndex = -1;
        document.getElementById("slideMenuPDF").tabIndex = -1;
        if (document.getElementById("begin"))
            document.getElementById("begin").tabIndex = -1;
        if (document.getElementById("end"))
            document.getElementById("end").tabIndex = -1;
        if (document.getElementById("PrevTopicButton"))
            document.getElementById("PrevTopicButton").tabIndex = -1;
        if (document.getElementById("NextTopicButton"))
            document.getElementById("NextTopicButton").tabIndex = -1;
        const elements = document.querySelectorAll('.slideEntry');
        for (const element of elements)
            element.tabIndex = -1;
    },
    
    async prepareMenu()
    {

        await this.findSlideCount();


        this.createMenu();

    },

    async findSlideCount()
    {
        if (localStorage.getItem(classnum + "_topic_" + (topicNum)) !== null)
        {
            this.SLIDE_COUNT = parseInt(localStorage.getItem(classnum + "_topic_" + (topicNum)), 10);
            return;
        }

        let slide = 1;

        var loop_var = 0;

        while(loop_var === 0)
        {

            const file = "./" +
                String(slide)
                .padStart(2,"0")
                +
                ".html";

            try
            {
                const response = await fetch(file, {method:"HEAD"});

                if(!response.ok)
                    loop_var = 1;
            }
            catch(error)
            {
                loop_var = 1;
            }
                
            slide++;
        }

        this.SLIDE_COUNT =
            slide - 2;

        localStorage.setItem(classnum + "_topic_" + (topicNum), (((this.SLIDE_COUNT < 10) ? "0" : "") + (this.SLIDE_COUNT)));
    },

    createMenu()
    {

        this.MENU.innerHTML = "";

        const interelem =
            document.createElement("div");

        interelem.className =
            "slideMenuInterElem";

        this.MENU.appendChild(interelem);

        const header =
            document.createElement("div");

        header.className =
            "slideMenuHeader";

        const top_button_container =
            document.createElement("div");

        top_button_container.className =
            "slideMenuButtonsTop";

        const close =
            document.createElement("button");

        close.id =
            "slideMenuClose";

        close.textContent =
            "×";

        close.title = 'Close the menu';

        close.tabIndex = -1;

        close.addEventListener(
            "click",
            () => this.closeMenu()
        );

        top_button_container.appendChild(close);

        const pdf =
            document.createElement("button");

        pdf.id =
            "slideMenuPDF";

        pdf.textContent =
            "PDF";

        pdf.title =
            "Open slides as a PDF";

        pdf.tabIndex = -1;

        pdf.addEventListener(
            "click",
            () => {window.open('../pdfs/cisc_' + classnum + '_topic_' + (((topicNum < 10) ? "0" : "") + topicNum) + '_lecture_notes.pdf', '_blank');}
        );

        top_button_container.appendChild(pdf);

        header.appendChild(top_button_container);

        const title =
            document.createElement("h3");

        title.className =
            "slideMenuTitle";

        title.textContent =
            "Topic "
            +
            topicNum;

        header.appendChild(title);

        const info =
            document.createElement("span");

        info.className =
            "infolink";

        info.title =
            "Info & Tips";

        info.alt =
            "Information and tips on how to use this menu.";

        info.textContent = "?";

        const inst =
            document.createElement("span");

        inst.id =
            "inst";

        inst.innerHTML = "<p><span>Info & Tips</span>1. Hover over a slide link to see the slide's preview.<br>2. Press &#9243; or &times; to close this menu.<br>3. <b>NEW</b>: Press the &#11013;&#65039; or &#10145;&#65039; keyboard arrow keys anytime to move between slides!<br>4. Got a touchscreen? Swipe right or left <u>with two fingers</u> (&#9996;&#127997;) to move between slides!</p>";

        title.appendChild(info);
        title.appendChild(inst);

        const navigation_top =
            document.createElement("div");

        var begin, end;

        navigation_top.className =
            "slideMenuButtons";

        if (pageNum !== 1)
        {
            begin =
                document.createElement("button");

            begin.id =
                "begin";

            begin.textContent =
                "← Slide 1";

            begin.title =
                "Go to Slide 1 (first slide)";

            begin.tabIndex = -1;

            begin.onclick =
                () =>
                {
                    this.changeSlide(0);
                };

            begin.addEventListener(
                "mouseenter",
                (event) =>
                {
                    this.startPreview(
                        "01",
                        1,
                        topicNum,
                        event
                    );
                }
            );

            begin.addEventListener(
                "mouseleave",
                () =>
                {
                    this.hidePreview();
                }
            );
        }

        const separator_top =
            document.createElement("hr");

        separator_top.style.margin = 0;
        separator_top.style.padding = 0;

        if (pageNum !== this.SLIDE_COUNT)
        {
            end =
                document.createElement("button");

            end.id =
                    "end";

            end.textContent =
                "Slide " + this.SLIDE_COUNT + " →";

            end.title =
                "Go to Slide " + this.SLIDE_COUNT + " (last slide)";

            end.tabIndex = -1;

            end.onclick =
                () =>
                {
                    this.changeSlide(1);
                };

            end.addEventListener(
                "mouseenter",
                (event) =>
                {
                    this.startPreview(
                        String(this.SLIDE_COUNT).padStart(2,"0"),
                        this.SLIDE_COUNT,
                        topicNum,
                        event
                    );
                }
            );

            end.addEventListener(
                "mouseleave",
                () =>
                {
                    this.hidePreview();
                }
            );
        }

        if (pageNum !== 1)
            navigation_top.appendChild(begin);
        if (pageNum !== 1 && pageNum !== this.SLIDE_COUNT)
            navigation_top.appendChild(separator_top);
        if (pageNum !== this.SLIDE_COUNT)
            navigation_top.appendChild(end);

        header.appendChild(navigation_top);

        interelem.appendChild(header);

        const slide_list_area =
            document.createElement("div");

        slide_list_area.className =
            "slideListArea";

        slide_list_area.tabIndex = -1;

        interelem.appendChild(slide_list_area);

        for(
            let i = 1;
            i <= this.SLIDE_COUNT;
            i++
        )
        {
            this.createSlideLink(i);
        }

        const navigation =
            document.createElement("div");

        var previous, next;

        navigation.className =
            "slideMenuButtons";

        navigation.tabIndex = -1;

        if (topicNum !== 1)
        {
            previous =
                document.createElement("button");

            previous.id =
                "PrevTopicButton";

            previous.textContent =
                "← Topic " + (topicNum - 1);

            previous.title =
                "Go to Topic " + (topicNum - 1) + ", Slide 1";

            previous.tabIndex = -1;

            previous.onclick =
                () =>
                {
                    this.changeTopic(-1);
                };

            previous.addEventListener(
                "mouseenter",
                (event) =>
                {
                    this.startPreview(
                        "../topic_" + String(topicNum - 1).padStart(2,"0") + "/01",
                        1,
                        String(topicNum - 1),
                        event
                    );
                }
            );

            previous.addEventListener(
                "mouseleave",
                () =>
                {
                    this.hidePreview();
                }
            );
        }

        const separator =
            document.createElement("hr");

        separator.style.margin = 0;
        separator.style.padding = 0;

        var nextTopicExists = 1;

        fetch("../topic_" + String(topicNum + 1).padStart(2,"0") + "/01.html", { method: 'HEAD' })
            .then(response => {
                if (!response.ok)
                    nextTopicExists = 0;
            })
            .catch(error => {nextTopicExists = 0});

        if (nextTopicExists !== 0)
        {
            next =
                document.createElement("button");

            next.id =
                "NextTopicButton";

            const nextTopicString = (topicNum + 1) + "";

            next.textContent =
                "Topic " + nextTopicString + " →";

            next.title =
                "Go to Topic " + nextTopicString + ", Slide 1";

            next.tabIndex = -1;

            next.onclick =
                () =>
                {
                   this.changeTopic(1);
                };

            next.addEventListener(
                "mouseenter",
                (event) =>
                {
                    this.startPreview(
                        "../topic_" + nextTopicString.padStart(2,"0") + "/01",
                        1,
                        nextTopicString,
                        event
                    );
                }
            );

            next.addEventListener(
                "mouseleave",
                () =>
                {
                    this.hidePreview();
                }
            );
        }

        if (topicNum !== 1)
            navigation.appendChild(previous);
        if (topicNum !== 1 && nextTopicExists !== 0)
            navigation.appendChild(separator);
        if (nextTopicExists !== 0)
            navigation.appendChild(next);

        interelem.appendChild(navigation);
    },

    createSlideLink(number)
    {
        var link;

        if (number === pageNum)
        {
            link =
                document.createElement("span");

            link.textContent =
                "Slide "
                +
                number;

            link.className =
                "slideEntry";

            link.classList.add(
                "current"
            );
        }
        else
        {
            link =
                document.createElement("a");

            link.title = "Go to slide " + number;

            link.tabIndex = -1;

            link.href =
                String(number).padStart(2,"0")
                +
                ".html";

            link.textContent =
                "Slide "
                +
                number;

            link.className =
                "slideEntry";

            link.addEventListener(
                "mouseenter",
                (event) =>
                {
                    this.startPreview(
                        String(number).padStart(2,"0"),
                        number,
                        topicNum,
                        event
                    );
                }
            );

            link.addEventListener(
                "mouseleave",
                () =>
                {
                    this.hidePreview();
                }
            );
        }

        document.getElementsByClassName('slideListArea')[0].appendChild(link);
    },

    changeTopic(direction)
    {
        const newTopic =
            Number(
                this.TOPIC_NUMBER
            )
            +
            direction;

        if(newTopic < 1)
            return;

        const folder =
            "topic_"
            +
            String(newTopic)
            .padStart(2,"0");

        location.href =
            "../"
            +
            folder
            +
            "/01.html";
    },

    changeSlide(type)
    {
        if(type === 0)
            location.href = "./01.html";
        else
            location.href = "./" + this.SLIDE_COUNT + ".html";
    },

    scrollToCurrentSlide()
    {
        const current =
            this.MENU.querySelector(
                ".current"
            );

        if(current)
        {
            current.scrollIntoView(
            {
                behavior:"smooth",

                block:"center"
            });
        }
    },

    startPreview(slidePath, slide, topic, event)
    {
        this.cancelPreview();

        this.HOVER_TIMER =
            setTimeout(
                () =>
                {
                    this.showPreview(
                        slidePath,
                        slide,
                        topic,
                        event
                    );

                },
                this.HOVER_DELAY
            );
    },

    cancelPreview()
    {
        clearTimeout(
            this.HOVER_TIMER
        );
    },

    showPreview(slidePath, slide, topic, event)
    {
        const newSource =
            slidePath + ".html";

        if (this.FRAME.src !==
            new URL(newSource, location.href).href)
        {
            this.POPUP.classList.add("loading");

            this.FRAME.onload =
                () =>
                {
                    this.scalePreview();

                    this.POPUP.classList.remove(
                        "loading"
                    );
                };

             this.FRAME.src =
                 newSource;
        }

        this.positionPreview(
            event
        );

        document.getElementById("previewTitle").textContent = "Slide " + slide + " of Topic " + topic;

        this.POPUP.classList.add(
            "visible"
        );
    },

    hidePreview()
    {
        this.POPUP.classList.remove(
            "visible"
        );

        clearTimeout(
            this.HOVER_TIMER
        );
    },

    positionPreview(event)
    {
        const margin = 10;
        const gap = 20;

        const portrait =
            window.matchMedia("(orientation: portrait)").matches;

        if(portrait)
        {
            this.POPUP.style.width =
                (window.innerWidth - 2 * margin) + "px";

            this.POPUP.style.height =
                Math.round((window.innerWidth - 2 * margin) * 0.48) + "px";
        }
        else
        {
            this.POPUP.style.width =
                "420px";

            this.POPUP.style.height =
                "calc(189px + 1.2vh + 1.2vw)";
        }

        this.scalePreview();

        const popupWidth =
            this.POPUP.offsetWidth;

        const popupHeight =
            this.POPUP.offsetHeight;

        let left;
        let top;

        if(portrait)
        {
            left = margin;

            top =
                event.clientY -
                popupHeight -
                gap;

            if(top < margin)
            {
                top =
                    event.clientY +
                    gap;
            }
        }
        else
        {
            left =
                event.clientX +
                gap;

            top =
                event.clientY -
                popupHeight / 2;

            if(left + popupWidth >
               window.innerWidth - margin)
            {
                left =
                    event.clientX -
                    popupWidth -
                    gap;
            }
        }

        left =
            Math.max(
                margin,
                Math.min(
                    left,
                    window.innerWidth -
                    popupWidth -
                    margin
                )
            );

        top =
            Math.max(
                margin,
                Math.min(
                    top,
                    window.innerHeight -
                    popupHeight -
                    margin
                )
            );

        this.POPUP.style.left =
            left + "px";

        this.POPUP.style.top =
            top + "px";

    },

    enableKeyboardControls()
    {
        document.addEventListener(
            "keydown",
            event =>
            {
                if(event.key === "Escape")
                    this.closeMenu();
            }
        );

    },

    scalePreview()
    {
        const slideWidth = 1280;
        const slideHeight = 577.33;

        const popupWidth =
            this.POPUP.clientWidth;

        const popupHeight =
            this.POPUP.clientHeight;

        const scale =
            Math.min(
                popupWidth / slideWidth,
                popupHeight / slideHeight
            );

        this.FRAME.style.width =
            slideWidth + "px";

        this.FRAME.style.height =
            slideHeight + "px";

        this.FRAME.style.transform =
            "scale(" + scale + ")";
        },
};
