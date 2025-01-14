#include <WiFi.h>
#include <HTTPUpdate.h>
 
/**********根据实际修改**********/
const char *wifi_ssid = "XAWZ";        // WIFI名称，区分大小写，不要写错
const char *wifi_password = "Xaw123456"; // WIFI密码
// const char *wifi_ssid = "iPhone 13";        // WIFI名称，区分大小写，不要写错
// const char *wifi_password = "t12345678"; // WIFI密码
//远程固件链接，只支持http
const char *ota_url = "http://192.168.22.82:8080/api/download?filename=firmware.bin&token=673066e669c9bf12ff4c4c9917f73274&timestamp=1732088898118";
/**********根据实际修改**********/
 
//当升级开始时，打印日志
void update_started()
{
    Serial.println("CALLBACK:  HTTP update process started");
}
 
//当升级结束时，打印日志
void update_finished()
{
    Serial.println("CALLBACK:  HTTP update process finished");
}
 
//当升级中，打印日志
void update_progress(int cur, int total)
{
    Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes[%.1f%%]...\n", cur, total, cur * 100.0 / total);
}
 
//当升级失败时，打印日志
void update_error(int err)
{
    Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}
 
/**
* @brief 固件升级函数，通过http请求获取远程固件，实现升级
*
* @param update_url 待升级远程固件bin文件的地址
* @return t_httpUpdate_return 升级最终状态
*/
t_httpUpdate_return updateBin(const char *update_url)
{
    Serial.println("start update");
    WiFiClient UpdateClient;
 
    httpUpdate.onStart(update_started);     //当升级开始时
    httpUpdate.onEnd(update_finished);      //当升级结束时
    httpUpdate.onProgress(update_progress); //当升级中
    httpUpdate.onError(update_error);       //当升级失败时
 
    t_httpUpdate_return ret = httpUpdate.update(UpdateClient, update_url);
 
    return ret;
}
 
/**
 * @brief  WIFI连接并ota升级
 *
 * @details
 * 1.连接wifi
 * 2.ota升级
 * @note
 * 1.请在ota_url中填写固件的http链接
 * 2.请在wifi_ssid和wifi_password中填写wifi的ssid和密码
 */
void OTA_setup(void)
{
    Serial.begin(115200); //波特率115200
    Serial.print("Connection WIFI");
    WiFi.begin(wifi_ssid, wifi_password); //连接wifi
    while (WiFi.status() != WL_CONNECTED)
        { //等待连接wifi
            delay(500);
            Serial.print(".");
        }
    Serial.println("");
    t_httpUpdate_return ret = updateBin(ota_url); //开始升级
    switch (ret)
        {
            case HTTP_UPDATE_FAILED: //当升级失败
                Serial.println("[update] Update failed.");
                break;
            case HTTP_UPDATE_NO_UPDATES: //当无升级
                Serial.println("[update] Update no Update.");
                break;
            case HTTP_UPDATE_OK: //当升级成功
                Serial.println("[update] Update ok.");
                break;
        }
}
 

 