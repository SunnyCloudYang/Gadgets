chrome.storage.sync.get(['autoReload'], ({ autoReload }) => {
    if (autoReload) {
        console.log("Auto-reload: Auto reload is running");
        let cnt = 0;
        let exist = setInterval(() => {

            if (document.getElementsByClassName("box").length) {
                if (document.getElementsByClassName("box box-tip").length
                    && document.getElementsByClassName("box box-tip")[0].getElementsByTagName("a").length) {
                    
                    chrome.storage.sync.get(['try_times'], ({ try_times }) => {

                        if (Reload()) {
                            cnt++;
                            console.log("Auto-reload: Try " + cnt + " times.");
                            if (cnt > try_times - 1) {
                                clearInterval(exist);
                                console.log("Auto-reload: Failed to reload, please check your Internet.");
                            }
                        }
                        else {
                            clearInterval(exist);
                        }

                    });
                    
                }
                else {
                    clearInterval(exist);
                    console.log("Auto-reload: Page loaded, auto-reload stops working.");
                }
            }
        }, 1500);
    }
});

function Reload() {
    let reload_href = document.getElementsByClassName("box box-tip")[0].getElementsByTagName("a")[0];
    console.log(reload_href);
    if (reload_href && reload_href.innerHTML == '重新加载') {
        reload_href.click();
        console.log("Auto-reload: Auto reloading...");
        return true;
    }
    else
        return false;
}
