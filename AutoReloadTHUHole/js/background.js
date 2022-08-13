let autoReload = true;
chrome.runtime.onInstalled.addListener(() => {
    chrome.storage.sync.set({ autoReload });
});

let try_times = 7;
chrome.runtime.onInstalled.addListener(() => {
    chrome.storage.sync.set({ try_times });
});