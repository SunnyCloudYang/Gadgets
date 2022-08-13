let toggle = document.getElementById('toggle');
chrome.storage.sync.get(['autoReload'], ({ autoReload }) => {
    autoReload === true ? toggle.checked = 'checked' : toggle.checked = null;
});

toggle.addEventListener("click", async () => {
    chrome.storage.sync.get(['autoReload'], ({ autoReload }) => {
        let reload = !autoReload;
        chrome.storage.sync.set({ autoReload: reload });
    });
});

let input_times = document.getElementById("times");
chrome.storage.sync.get(['try_times'], ({ try_times }) => {
    input_times.setAttribute("placeholder", try_times);
});

input_times.onkeydown = function (ev) {
    if (ev.which === 13) {
        saveTimes();
    }
}

function saveTimes() {
    let n = input_times.value;
    if (n) {
        chrome.storage.sync.set({ try_times: n });
        input_times.setAttribute("placeholder", n);
        input_times.value = null;
        console.log("Auto-reload: Reset try times: " + n);
        alert("Reset try times: " + n);
    }
}
