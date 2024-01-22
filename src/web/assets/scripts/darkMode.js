let isDark = localStorage.getItem("darkMode");

if (isDark == null) {
    isDark = 'false';
}

function checkDarkMode() {
    localStorage.setItem("darkMode", isDark)

    if (isDark === 'true') {
        document.body.classList.add("dark-mode");
        document.body.classList.remove("light-mode");
    } else {
        document.body.classList.add("light-mode");
        document.body.classList.remove("dark-mode");
    }
}

$( "#toggleDarkMode" ).button();

$( function () {
    $( "#toggleDarkMode" ).click( function( event ) {
        event.preventDefault();

        if (isDark === 'true') {
            isDark = 'false';
        } else {
            isDark = 'true';
        }

        checkDarkMode();
    });
});

document.addEventListener("DOMContentLoaded", (event) => { 
    checkDarkMode();
});
