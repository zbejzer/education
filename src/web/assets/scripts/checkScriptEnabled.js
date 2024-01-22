window.addEventListener("load", (event) => {
    const jsFeatures = document.querySelectorAll(".js-dependant");

    jsFeatures.forEach((element) => {
        element.classList.remove('js-dependant');
    });
});