chrome.storage.sync.get(['autoReload'], ({ autoReload }) => {

    if (autoReload) {

        let url = window.location.href;

        if (url.indexOf("t-hole.github.io") != -1)
            ReloadT_Hole();

        else if (url.indexOf("bbs.pku.edu.cn/v2") != -1)
            ReloadPKU();

        else if (url.indexOf("planet.tsinghua.edu.cn/member.php") != -1)
            ReloadTHU();

        else if (url == "https://cn.bing.com/") {
            console.log("THUSurfHelper: Remove scroll bar.");
            document.getElementsByTagName("html")[0].style.overflowY = "hidden";
        }

        else if (url.indexOf("https://zhjwxk.cic.tsinghua.edu.cn/xklogin.do") != -1)
            LoginCRS();
    }

});

function ReloadT_Hole() {
    console.log("Auto-reload: Auto reload is running");
    let cnt = 0;
    const interv = 1500;
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

function ReloadPKU() {

    const dialog_welcome = document.getElementById("dialog-welcome");

    if (dialog_welcome) {
        const reload = dialog_welcome.getElementsByClassName("button red")[0];
        if (reload.innerHTML.indexOf("进入未名BBS") != -1)
            reload.click();
        else
            console.log("Helper: Failed to jump to PKU BBS, please login first or check your Internet.");
    }
}

function ReloadTHU() {
    const message = document.getElementById("messagetext").getElementsByClassName("alert_btnleft")[0];
    
    if (message.innerHTML.match("如果您的浏览器没有自动跳转，请点击此链接").index != -1)
        message.getElementsByTagName("a")[0].click();
    else
        console.log("Helper: Failed to jump to 1911 planet, please login first or check your Internet.");
}

function LoginCRS() {

    console.log("THUSurfHelper: Input box helper.")

    const captcha = document.getElementsByName("_login_image_")[0];
    const username = document.getElementById("j_username");
    const password = document.getElementById("j_password");
    const login_btn = document.getElementById("button").getElementsByTagName("a")[0];

    captcha.onkeydown = username.onkeydown = password.onkeydown = function (e) {
        if (e.key == "Enter") {
            if (username.value == "")
                username.focus();
            else if (password.value == "")
                password.focus();
            else if (captcha.value == "")
                captcha.focus();
            else {
                console.log("THUSurfHelper: Login...");
                login_btn.click();
            }
        }
    }
}