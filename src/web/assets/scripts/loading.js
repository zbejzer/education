Pace.on('done', async function () {
    $( "#loading-cover" ).fadeOut(function () {
        removeNoScript();
        $( "#loading-cover" ).hide(0);
    });
});