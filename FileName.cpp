
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat img(500, 900, CV_8UC3, Scalar(255, 255, 255));
Point ptPrev(-1, -1);
Rect save(500, 0, 200, 100);
Rect load(500, 100, 200, 100);
Rect clear(500, 200, 200, 100);
Rect run(500, 300, 200, 100);
Rect exitt(500, 400, 200, 100);
Rect contours(700, 0, 200, 100);
Rect feature2(700, 100, 200, 100);
Rect feature3(700, 200, 200, 100);
void onMouse1(int event, int x, int y, int flags, void*);
void Save();
void Load();
void Clear();
void Run();
void Exit();
void Contours();
void Feature2();
void Feature3();
void drawButtons();
int main()
{
    drawButtons();
    namedWindow("img");
    setMouseCallback("img", onMouse1);
    imshow("img", img);
    waitKey(0);
    return 0;
}
void onMouse1(int event, int x, int y, int flags, void*)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        if (x < 500)
        {
            ptPrev = Point(x, y);
        }
        else {
            Point clickPoint(x, y);
            if (save.contains(clickPoint)) {
                Save();
            }
            else if (load.contains(clickPoint)) {
                Load();
            }
            else if (clear.contains(clickPoint)) {
                Clear();
            }
            else if (run.contains(clickPoint)) {
                Run();
            }
            else if (exitt.contains(clickPoint)) {
                Exit();
            }
            else if (contours.contains(clickPoint)) {
                Contours();
            }
            else if (feature2.contains(clickPoint)) {
                Feature2();
            }
			else if (feature3.contains(clickPoint)) {
				Feature3();
			}
        }
    }
    else if (event == EVENT_LBUTTONUP) {
        ptPrev = Point(-1, -1);
    }
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
        if (x < 500 && x >= 0 && y < 500 && y >= 0) {
            line(img, ptPrev, Point(x, y), Scalar::all(0), 10);
            ptPrev = Point(x, y);
            imshow("img", img);
        }
    }
}
void drawButtons()
{
    rectangle(img, save, Scalar(0, 0, 0), 2);
    putText(img, "Save", Point(save.x + 10, save.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, load, Scalar(0, 0, 0), 2);
    putText(img, "Load", Point(load.x + 10, load.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, clear, Scalar(0, 0, 0), 2);
    putText(img, "Clear", Point(clear.x + 10, clear.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, run, Scalar(0, 0, 0), 2);
    putText(img, "Run", Point(run.x + 10, run.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, exitt, Scalar(0, 0, 0), 2);
    putText(img, "Exit", Point(exitt.x + 10, exitt.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, contours, Scalar(0, 0, 0), 2);
    putText(img, "contours", Point(contours.x + 10, contours.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, feature2, Scalar(0, 0, 0), 2);
    putText(img, "feature2", Point(feature2.x + 10, feature2.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
	rectangle(img, feature3, Scalar(0, 0, 0), 2);
	putText(img, "feature3", Point(feature3.x + 10, feature3.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
}
void Save()
{
    string fileName;
    cout << "���ϸ� �Է�: ";
    cin >> fileName;
    Mat saveImg = img(Rect(0, 0, 500, 500)).clone();
    resize(saveImg, saveImg, Size(500, 500));
    imwrite(fileName, saveImg);
    cout << fileName + " ������ �����" << endl;
}
void Load()
{
    string fileName;
    cout << "���ϸ� �Է�: ";
    cin >> fileName;
    Mat src = imread(fileName);
    if (!src.empty()) {
        src.copyTo(img(Rect(0, 0, 500, 500)));
        imshow("img", img);
        cout << fileName + " ������ �ҷ���" << endl;
    }
    else {
        cout << "������ �ҷ��� �� �����ϴ�." << endl;
    }
}
void Clear()
{
    img(Rect(0, 0, 500, 500)) = Scalar(255, 255, 255);
    drawButtons();
    imshow("img", img);
    cout << "�Է�â ������" << endl;
}
void Run()
{
	Mat gray, binary;
	cvtColor(img(Rect(1, 1, 490, 490)), gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 100, 255, THRESH_BINARY_INV);
	vector<vector<Point>> contours;
	findContours(binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	Mat drawing = Mat::zeros(binary.size(), CV_8UC3);
	int boundingBoxCount = 0;
	vector<Rect> boundingBoxes;

	for (size_t i = 0; i < contours.size(); i++) {
		Rect boundRect = boundingRect(contours[i]);
		rectangle(drawing, boundRect.tl(), boundRect.br(), Scalar(255, 255, 255), 2);
		boundingBoxes.push_back(boundRect);
		boundingBoxCount++;
	}
	vector<Point2f> centers;
	for (size_t i = 0; i < boundingBoxes.size(); i++) {
		Rect boundRect = boundingBoxes[i];
		Point2f center((boundRect.tl().x + boundRect.br().x) / 2.0, (boundRect.tl().y + boundRect.br().y) / 2.0);
		centers.push_back(center);
	}
	if (boundingBoxCount == 3)
		cout << "�ν� ���: 8" << endl;
	else if (boundingBoxCount == 2) {
		Rect firstBox = boundingBoxes[0];
		Rect secondBox = boundingBoxes[1];
		int centerY1 = (firstBox.tl().y + firstBox.br().y) / 2;
		int centerY2 = (secondBox.tl().y + secondBox.br().y) / 2;
		if (centerY1 > centerY2)
			cout << "�ν� ���: 6" << endl;
		else if (centerY1 < centerY2)
			cout << "�ν� ���: 9" << endl;
		else if (abs(centerY1 - centerY2) < 30)
			cout << "�ν� ���: 0" << endl;
	}
	else if (boundingBoxCount == 1)
		cout << "�ν� ���: 1" << endl;
	else
		cout << "�νĵ� ���ڰ� �����ϴ�." << endl;
	cout << endl;
}
void Exit()
{
    cout << "���α׷� ����" << endl;
    destroyAllWindows();
    exit(0);
}
void Contours()
{
    Mat gray, binary;
    cvtColor(img(Rect(1, 1, 490, 490)), gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 100, 255, THRESH_BINARY_INV);
    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
    int contourCount = contours.size();
    cout << "�ܰ����� ����: " << contourCount << "��" << endl;
}
void Feature2()
{

	Mat gray, thresh, morph, cen, binary;
	cvtColor(img(Rect(1, 1, 490, 490)), gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 100, 255, THRESH_BINARY_INV);
	vector<vector<Point>> contours;
	findContours(binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
	int contourCount = contours.size();
	cout << "�ܰ����� ����: " << contourCount << "��" << endl;
	Mat dst = img(Rect(1, 1, 497, 497)).clone();
	resize(dst, dst, Size(500, 500));
	cvtColor(dst, gray, COLOR_BGR2GRAY);
	threshold(gray, thresh, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	morphologyEx(thresh, morph, MORPH_CLOSE, Mat(20, 20, CV_8UC1));
	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(morph, labels, stats, centroids);
	findContours(morph, contours, RETR_LIST, CHAIN_APPROX_NONE);
	cvtColor(morph, cen, COLOR_GRAY2BGR);
	vector<Point> center;
	for (int i = 0; i < contours.size(); i++) {
		Point centroid(0, 0);
		for (int j = 0; j < contours[i].size(); j++) {
			centroid.x += contours[i][j].x;
			centroid.y += contours[i][j].y;
		}
		centroid.x /= contours[i].size();
		centroid.y /= contours[i].size();
		center.push_back(centroid);
		cout << "�ܰ��� " << i + 1 << "�� �����߽�: (" << center[i].x << ", " << center[i].y << ")" << endl;
		circle(cen, center[i], 5, Scalar(0, 0, 255), -1);
	}
}
void Feature3()
{
    Mat binaryImage = img(Rect(1, 1, 498, 498)).clone();
    resize(binaryImage, binaryImage, Size(500, 500));
    Mat gray, bin, final1;
    int minX = INT_MAX, minY = INT_MAX, maxX = 0, maxY = 0;
    cvtColor(binaryImage, gray, COLOR_BGR2GRAY); 
    threshold(gray, bin, 0, 255, THRESH_BINARY_INV | THRESH_OTSU); 
    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    cvtColor(bin, final1, COLOR_GRAY2BGR);
    for (const auto& contour : contours) { 
        for (const auto& point : contour) { 
            minX = min(minX, point.x);
            minY = min(minY, point.y);
            maxX = max(maxX, point.x);
            maxY = max(maxY, point.y);
        }
        rectangle(final1, Point(minX, minY), Point(maxX, maxY), Scalar(0, 0, 255), 2);
    }
    Mat save = binaryImage(Rect(minX, minY, maxX - minX, maxY - minY)).clone();
    imshow("Contours", save);
}
