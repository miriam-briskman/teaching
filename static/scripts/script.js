var pageMode = localStorage.getItem("mode");
if (pageMode != "light" && pageMode != "dark")
    localStorage.setItem("mode", "light");
var pageMode = localStorage.getItem("mode");
if (pageMode == "light")
    document.getElementById("darkstyle").disabled = true;
else if (pageMode == "dark")
    document.getElementById("lightstyle").disabled = true;

function revealInfo()
{
    var pageMode = localStorage.getItem("mode");
    var contents = document.getElementsByClassName("contents");
    for (var i = 0; i < contents.length; i++) {
	contents.item(i).style.opacity = "0";
	contents.item(i).style.visibility = "hidden";
	contents.item(i).style.display = "none";
    }
    var tabs = document.getElementsByClassName("tab");
    for (var i = 0; i < tabs.length; i++)
    {
	if (pageMode == "light")
	{
	    tabs.item(i).style.borderBottom = "1pt solid black";
	    tabs.item(i).style.color = "rgb(133,0,65)";
	}
	else if (pageMode == "dark")
	{
	    tabs.item(i).style.borderBottom = "1pt solid white";
	    tabs.item(i).style.color = "rgb(235, 222, 86)";
	}
	tabs.item(i).style.cursor = "pointer";
    }
    var myelem = event.srcElement;
    var myelemInnerHTML = myelem.innerHTML.toLowerCase();
    window.location.hash = "#" + myelemInnerHTML;
    document.getElementById("x" + myelemInnerHTML).style.display = "block";
    setTimeout(function(){
	document.getElementById("x" + myelemInnerHTML).style.opacity = "1";
	document.getElementById("x" + myelemInnerHTML).style.visibility = "visible";
    }, 1);
    event.srcElement.style.borderBottom = "0";
    if (pageMode == "light")
	event.srcElement.style.color = "black";
    else if (pageMode == "dark")
	event.srcElement.style.color = "white";
    event.srcElement.style.cursor = "default";
    sessionStorage.setItem("tab", "" + myelemInnerHTML);
}

const currentHash = window.location.hash;

var openTab = sessionStorage.getItem("tab");
if (currentHash === undefined || currentHash.length === 0)
{
    if (openTab === null)
        openTab = "teaching";
    else
        window.location.hash = "#" + openTab;
}
else
{
    openTab = currentHash.substring(1).toLowerCase();
    const tabSet = ["teaching", "service", "guides", "bio", "contact", "faq"];
    if (!tabSet.includes(openTab))
        openTab = "teaching";
}

function scrollBar ()
{
    /* The code below is based on https://stackoverflow.com/a/76066874/14167156 */
    const box = document.getElementsByClassName('tabs')[0];
    let isDown = false;
    let startX;
    let scrollLeft;

    box.addEventListener('mousedown', (e) => {
	isDown = true;
	startX = e.pageX - box.offsetLeft;
	scrollLeft = box.scrollLeft;
    });

    box.addEventListener('mouseleave', () => {
	isDown = false;
    });

    box.addEventListener('mouseup', () => {
	isDown = false;
    });

    document.addEventListener('mousemove', (e) => {
	if (!isDown)
	    return;
	e.preventDefault();
	const x = e.pageX - box.offsetLeft;
	const walkX = (x - startX) * 1; // Change this number to adjust the scroll speed
	box.scrollLeft = scrollLeft - walkX;
    });
}

function switchFocus (flag)
{
    const element = document.querySelector('#switch-input');

    if (flag == true)
    {
        var pageMode = localStorage.getItem("mode");
	if (pageMode == "dark")
	    document.getElementById('switch-container').style.border = '2px dashed white';
	else
	    document.getElementById('switch-container').style.border = '2px dashed black';
    } 
    else
    {
        if (element.matches(':focus-visible'))
        {
            var pageMode = localStorage.getItem("mode");
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
    var pageMode = localStorage.getItem("mode");
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
    var pageMode = localStorage.getItem("mode");
    var tabs = document.getElementsByClassName("tab");
    if (pageMode == "light")
    {
        document.getElementById("darkstyle").disabled = false;
        document.getElementById("lightstyle").disabled = true;
        document.styleSheets[0].insertRule(".tabs.is-pinned { background-color: #10162a !important; }", 0);
        for (var i = 0; i < tabs.length; i++)
        {
            tabs.item(i).style.borderBottom = "1pt solid white";
            tabs.item(i).style.color = "rgb(235, 222, 86)";
        }
        let openTab = sessionStorage.getItem("tab");
        if (openTab === null)
            openTab = "teaching";
        else
            window.location.hash = "#" + openTab;
        document.getElementById(openTab + "-tab").style.color = "white";
        document.getElementById(openTab + "-tab").style.borderBottom = "unset";
        document.getElementById("slider").title = "Change to light/dark mode [dark mode is on]";
        localStorage.setItem("mode", "dark");
    }
    else
    {
        document.getElementById("darkstyle").disabled = true;
        document.getElementById("lightstyle").disabled = false;
        document.styleSheets[0].insertRule(".tabs.is-pinned { background-color: #f4f9fe !important; }", 0);
        for (var i = 0; i < tabs.length; i++)
        {
            tabs.item(i).style.borderBottom = "1pt solid black";
            tabs.item(i).style.color = "rgb(133,0,65)";
        }
        let openTab = sessionStorage.getItem("tab");
        if (openTab === null)
            openTab = "teaching";
        else
            window.location.hash = "#" + openTab;
        document.getElementById(openTab + "-tab").style.color = "black";
        document.getElementById(openTab + "-tab").style.borderBottom = "unset";
        document.getElementById("slider").title = "Change to light/dark mode [light mode is on]";
        localStorage.setItem("mode", "light");
    }
}

function escapeRegExp(string)
{
    return string.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
}

function highlightText(element, searchTerm) {
    if (!searchTerm.trim()) return;

    const escaped = escapeRegExp(searchTerm);
    const regex = new RegExp(escaped, "gi");

    const walker = document.createTreeWalker(
        element,
        NodeFilter.SHOW_TEXT,
        {
            acceptNode(node) {
                // Ignore empty text nodes
                if (!node.nodeValue.trim()) return NodeFilter.FILTER_REJECT;

                // Ignore text inside <script> or <style>
                const parent = node.parentNode;
                if (parent && (parent.tagName === "SCRIPT" || parent.tagName === "STYLE")) {
                    return NodeFilter.FILTER_REJECT;
                }

                return NodeFilter.FILTER_ACCEPT;
            }
        }
    );

    const textNodes = [];
    while (walker.nextNode()) {
        textNodes.push(walker.currentNode);
    }

    textNodes.forEach(node => {
        if (!regex.test(node.nodeValue)) return;

        const span = document.createElement("span");
        span.innerHTML = node.nodeValue.replace(regex, match => `<mark>${match}</mark>`);

        node.parentNode.replaceChild(span, node);
    });
}

function clearHighlights(element)
{
    /*element.querySelectorAll("mark").forEach(mark => {
        const textNode = document.createTextNode(mark.textContent);
        mark.parentNode.replaceChild(textNode, mark);
        mark.parentNode.normalize();
    });*/
    const marks = element.querySelectorAll("mark");

    marks.forEach(mark => {
        const parent = mark.parentNode;
        if (!parent) return;

        const textNode = document.createTextNode(mark.textContent);
        parent.replaceChild(textNode, mark);

        // Normalize only if parent still exists
        parent.normalize();
    });
}



function FAQSearch() 
{
    var input, filter, ul, li, i, noResults, count = 0;
    input = document.getElementById("FAQSearchBar");
    filter = input.value.toUpperCase();
    ul = document.getElementById("list-of-FAQ");
    li = ul.getElementsByTagName("li");
    noResults = document.getElementById("noSearchResults");
    for (i = 0; i < li.length; i++)
    {
        clearHighlights(li[i]);
        /*var text = li[i].innerHTML;
        var re1 = new RegExp("<mark>", "g");
        var re2 = new RegExp("</mark>", "g");
        var newText = text.replace(re1, '').replace(re2, '');
        li[i].innerHTML = newText;*/
        if (li[i].innerText.toUpperCase().indexOf(filter) > -1)
        {
            li[i].style.display = "";
            /*if ((filter.trim()).length > 0)
            {
                var text = li[i].innerHTML;
                var escapedInput = escapeRegExp(input.value);
                var re = new RegExp(escapedInput, "gi");
                var newText = text.replace(re, match => `<mark>${match}</mark>`);
                li[i].innerHTML = newText;
            }*/
            if (input.value.trim().length > 0)
                highlightText(li[i], input.value);
        }
        else
        {
            li[i].style.display = "none";
            count++;
        }
    }
    if (count === li.length)
        noResults.style.display = "block";
    else
        noResults.style.display = "none";
}

function eraseSearch()
{
    var ul = document.getElementById("list-of-FAQ");
    var li = ul.getElementsByTagName("li");
    document.getElementById("FAQSearchBar").value = "";
    for (let i = 0; i < li.length; i++) {
        clearHighlights(li[i]);
        li[i].style.display = "";
    }

    document.getElementById("noSearchResults").style.display = "none";
}
