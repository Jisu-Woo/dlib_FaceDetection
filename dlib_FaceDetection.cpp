#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;

int main()
{
    try
    {
        // Dlib의 전면 얼굴 감지기 로드
        frontal_face_detector detector = get_frontal_face_detector();
        // 얼굴 랜드마크 모델 로드 (사전에 다운로드한 모델 파일의 경로 지정)
        shape_predictor sp;
        deserialize("shape_predictor_68_face_landmarks.dat") >> sp;



        array2d<rgb_pixel> img1;
        // 이미지 로드 (이미지 파일 경로 지정)1
        load_image(img1, "C:/Users/gemge/OneDrive/바탕 화면/수지.jpeg");

        //array2d<rgb_pixel> img2;
        // 이미지 로드 (이미지 파일 경로 지정)2
        //load_image(img2, "C:/Users/gemge/OneDrive/바탕 화면/아이유.jpg");


        // 감지된 얼굴 리스트1
        std::vector<rectangle> dets1 = detector(img1);
        cout << "1. Number of faces detected: " << dets1.size() << endl;

        // 감지된 얼굴 리스트2
        //std::vector<rectangle> dets2 = detector(img2);
        //cout << "2. Number of faces detected: " << dets2.size() << endl;

         
        // 각 얼굴에 대해 랜드마크 추정 1
        std::vector<full_object_detection> shapes1;
        for (unsigned long i = 0; i < dets1.size(); ++i)
        {
            full_object_detection shape1 = sp(img1, dets1[i]);
            cout << "1. number of parts: " << shape1.num_parts() << endl;
            shapes1.push_back(shape1);
        }
        /*

        // 각 얼굴에 대해 랜드마크 추정 2
        std::vector<full_object_detection> shapes2;
        for (unsigned long i = 0; i < dets2.size(); ++i)
        {
            full_object_detection shape2 = sp(img2, dets2[i]);
            cout << "2. number of parts: " << shape2.num_parts() << endl;
            shapes2.push_back(shape2);
        }
        */

        /*
        for (int i = 1; i <= shapes1[0].num_parts(); i++) {
            (shapes1[0] - shapes2[0].get_rect()) ^ 2 * log(shapes1[0] - shapes2[0])

        }*/







        
        // 랜드마크를 화면에 표시 (빨간 점으로)
        image_window win;
        win.clear_overlay();
        win.set_image(img1);
        for (const auto& shape : shapes1) {
            for (unsigned long i = 0; i < shape.num_parts(); ++i) {
                win.add_overlay(image_window::overlay_circle(shape.part(i), 1.5, rgb_pixel(255, 0, 0)));
            }
        }
        




        cout << "Press any key to continue..." << endl;
        cin.get();
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
    return 0;
}
