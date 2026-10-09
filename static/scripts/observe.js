const el = document.querySelector(".tabs");
const observer = new IntersectionObserver( 
  ([e]) => e.target.classList.toggle("is-pinned", e.intersectionRatio < 1),
  { threshold: [1] }
);

observer.observe(el);

/*const stickyCols = document.querySelectorAll(".sticky-col");
const pinnedObserver = new IntersectionObserver(
  (entries) => {
    entries.forEach((entry) => {
      entry.target.classList.toggle("is-pinned", entry.intersectionRatio < 1);
    });
  },
  { threshold: [1]}
);

stickyCols.forEach((col) => pinnedObserver.observe(col));*/

/*const stickyCols = document.querySelectorAll(".sticky-col");

const pinnedObserver = new IntersectionObserver(
  (entries) => {
    entries.forEach((entry) => {
      // If NOT intersecting, it means it's stuck at the left edge
      entry.target.classList.toggle("is-pinned", !entry.isIntersecting);
    });
  },
  { 
    threshold: 0, // Trigger immediately when it touches the border
    rootMargin: "0px 0px 0px 0px" // Monitors the exact true edge of the container
  }
);

stickyCols.forEach((col) => pinnedObserver.observe(col));*/

/*// Find your scrollable container and all your sticky cells once upfront
const tableWrapper = document.querySelector(".table-wrapper");
const stickyCols = document.querySelectorAll(".sticky-col");

tableWrapper.addEventListener("scroll", () => {
  // Check if the scrollbar has moved from the left origin
  const isScrolledHorizontally = tableWrapper.scrollLeft > 0;
  
  // Loop through each sticky cell and toggle the class directly on it
  stickyCols.forEach((col) => {
    col.classList.toggle("is-pinned", isScrolledHorizontally);
  });
}, { passive: true });*/

// 1. Find all table wrappers on the page
const tableWrappers = document.querySelectorAll(".table-wrapper");

// 2. Loop through each individual table wrapper
tableWrappers.forEach((wrapper) => {
  // Find only the sticky columns that belong inside THIS specific wrapper
  const stickyCols = wrapper.querySelectorAll(".sticky-col");

  // 3. Attach a scroll listener to this specific wrapper
  wrapper.addEventListener("scroll", () => {
    // Check if this specific table has scrolled horizontally from its origin
    const isScrolledHorizontally = wrapper.scrollLeft > 0;
    
    // 4. Toggle the class ONLY on the columns inside this specific table
    stickyCols.forEach((col) => {
      col.classList.toggle("is-pinned", isScrolledHorizontally);
    });
  }, { passive: true });
});


