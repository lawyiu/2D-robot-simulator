(function() {
    "use strict";
    const selectElm = document.querySelector("#examples-selection");
    ace.config.set('basePath', 'https://cdnjs.cloudflare.com/ajax/libs/ace/1.4.12/');
    window.editor = ace.edit("program-editor");
    editor.setTheme("ace/theme/github");
    editor.session.setMode("ace/mode/c_cpp");
    editor.setShowPrintMargin(false);

    function addOption(selectElm, opStr, opVal) {
        var newOption = new Option(opStr, opVal);
        selectElm.appendChild(newOption);
    }

    function loadProgram(filename) {
        fetch("/examples/" + filename)
        .then(resp => resp.text())
        .then(data => {
            editor.setValue(data, 1);
        });
    }

    fetch("/examples/examples.json")
        .then(resp => resp.json())
        .then(data => {
            const examples = data.examples;
            for (let i in examples) {
                const example = examples[i];
                addOption(selectElm, example.file + " - " + example.description, example.file);
            }

            loadProgram(examples[0].file);
        });

    selectElm.addEventListener("change", function(event) {
        loadProgram(this.value);
        editor.focus();
    });
}());
