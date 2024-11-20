#include <opencv2/opencv.hpp> 
#include <quirc.h> 
#include <iostream> 
#include <cstring> 
#include <set> 
#include <fstream> 
#include <windows.h> 

using namespace cv;
using namespace std;
void createWiFiProfile(const string& ssid, const string& password) {
    string profile =
        "<?xml version=\"1.0\"?>\n"
        "<WLANProfile xmlns=\"http://www.microsoft.com/networking/WLAN/profile/v1\">\n"
        "    <name>" + ssid + "</name>\n"
        "    <SSIDConfig>\n"
        "        <SSID>\n"
        "            <name>" + ssid + "</name>\n"
        "        </SSID>\n"
        "    </SSIDConfig>\n"
        "    <connectionType>ESS</connectionType>\n"
        "    <connectionMode>auto</connectionMode>\n"
        "    <MSM>\n"
        "        <security>\n"
        "            <authEncryption>\n"
        "                <authentication>WPA2PSK</authentication>\n"
        "                <encryption>AES</encryption>\n"
        "                <useOneX>false</useOneX>\n"
        "            </authEncryption>\n"
        "            <sharedKey>\n"
        "                <keyType>passPhrase</keyType>\n"
        "                <protected>false</protected>\n"
        "                <keyMaterial>" + password + "</keyMaterial>\n"
        "            </sharedKey>\n"
        "        </security>\n"
        "    </MSM>\n"
        "</WLANProfile>";

    ofstream file("wifi_profile.xml");
    file << profile;
    file.close();
}
void connectToWiFi(const string& ssid) {
    system("netsh wlan add profile filename=\"wifi_profile.xml\"");
    string connect_command = "netsh wlan connect name=\"" + ssid + "\"";
    system(connect_command.c_str());
}

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Failed to open the camera" << endl;
        return -1;
    }
    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);

    struct quirc* qr = quirc_new();
    if (!qr) {
        cout << "Failed to initialize Quirc" << endl;
        return -1;
    }

    Mat frame;
    set<string> decoded_qr_codes;
    int box_size = 200;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        int center_x = frame.cols / 2;
        int center_y = frame.rows / 2;
        Point top_left(center_x - box_size / 2, center_y - box_size / 2);
        Point bottom_right(center_x + box_size / 2, center_y + box_size / 2);
        rectangle(frame, top_left, bottom_right, Scalar(0, 0, 0), 2);

        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(3, 3), 0);

        if (quirc_resize(qr, gray.cols, gray.rows) < 0) {
            cout << "Failed to resize Quirc buffer" << endl;
            return -1;
        }

        uint8_t* image_data = quirc_begin(qr, NULL, NULL);
        memcpy(image_data, gray.data, gray.cols * gray.rows);
        quirc_end(qr);

        int num_codes = quirc_count(qr);
        for (int i = 0; i < num_codes; i++) {
            struct quirc_code code;
            struct quirc_data data;
            quirc_extract(qr, i, &code);

            if (quirc_decode(&code, &data) == 0) {
                string payload((char*)data.payload);
                if (decoded_qr_codes.find(payload) == decoded_qr_codes.end()) {
                    decoded_qr_codes.insert(payload);
                    cout << "QR code detected: " << payload << endl;
                    size_t delimiter_pos = payload.find(';');
                    if (delimiter_pos != string::npos) {
                        string ssid = payload.substr(0, delimiter_pos);
                        string password = payload.substr(delimiter_pos + 1);

                        cout << "Attempting to connect to Wi-Fi SSID: " << ssid << endl;
                        createWiFiProfile(ssid, password);
                        connectToWiFi(ssid);
                    }

                    for (int j = 0; j < 4; j++) {
                        line(frame,
                            Point(code.corners[j].x, code.corners[j].y),
                            Point(code.corners[(j + 1) % 4].x, code.corners[(j + 1) % 4].y),
                            Scalar(0, 255, 0), 2);
                    }
                }
            }
            else {
                cout << "Failed to decode QR code" << endl;
            }
        }

        imshow("Camera", frame);
        if (waitKey(30) >= 0) break;
    }

    quirc_destroy(qr);
    cap.release();
    destroyAllWindows();
    return 0;
}



