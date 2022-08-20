chrome.storage.sync.get(['autoReload'], ({ autoReload }) => {
    if (autoReload) {
        console.log("Auto-reload: Auto reload is running");
        let cnt = 0;            //count reload times
        let interv = 1500;      //time interval of checking page
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
        }, interv);
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

let cnt = 0;
let intcpt = setInterval(() => {
    let wrapper;
    cnt++;
    cnt > 5 ? clearInterval(intcpt) : wrapper = document.getElementsByClassName("bdwm-dialog-wrapper bdwm-dialog-wrapper-background");
    if (wrapper && wrapper.length) {
        wrapper[0].setAttribute("style", "display:none");
        console.log("intercept welcome page");
        clearInterval(intcpt);
    }
}, 1000);

