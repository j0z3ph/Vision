using OpenCvSharp;
using System.Security.Cryptography;

namespace ConsoleTestCV {
    internal class Program {
        static void Main(string[] args) {
            VideoCapture capture = new VideoCapture(0);
            using Window window = new Window("Settings");
            using Window window2 = new Window("Video");

            using Mat image = new Mat();
            Vec3i lower = new Vec3i();
            Vec3i upper = new Vec3i();
            Mat element = Cv2.GetStructuringElement(MorphShapes.Ellipse, new Size(5, 5));

            int hMin = 0, sMin = 0, vMin = 0, hMax = 0, sMax = 0, vMax = 0;

            
            Cv2.CreateTrackbar("HMin", "Settings", 179);
            Cv2.CreateTrackbar("SMin", "Settings", 255);
            Cv2.CreateTrackbar("VMin", "Settings", 255);
            Cv2.CreateTrackbar("HMax", "Settings", 179);
            Cv2.CreateTrackbar("SMax", "Settings", 255);
            Cv2.CreateTrackbar("VMax", "Settings", 255);

            Cv2.SetTrackbarPos("HMax", "Settings", 179);
            Cv2.SetTrackbarPos("SMax", "Settings", 255);
            Cv2.SetTrackbarPos("VMax", "Settings", 255);


            while (Cv2.WaitKey(30) != 27) {
                if (capture.Read(image)) {
                    // Image processing
                    using Mat im2 = image.Blur(new Size(5, 5));
                    using Mat hsv = im2.CvtColor(ColorConversionCodes.BGR2HSV);

                    hMin = Cv2.GetTrackbarPos("HMin", "Settings");
                    sMin = Cv2.GetTrackbarPos("SMin", "Settings");
                    vMin = Cv2.GetTrackbarPos("VMin", "Settings");
                    hMax = Cv2.GetTrackbarPos("HMax", "Settings");
                    sMax = Cv2.GetTrackbarPos("SMax", "Settings");
                    vMax = Cv2.GetTrackbarPos("VMax", "Settings");

                    lower.Item0 = hMin;
                    lower.Item1 = sMin;
                    lower.Item2 = vMin;
                    upper.Item0 = hMax;
                    upper.Item1 = sMax;
                    upper.Item2 = vMax;
                    
                    
                    using Mat mask = hsv.InRange(lower, upper);
                    Mat res = new Mat();




                    Cv2.BitwiseAnd(image, image, res, mask);
                    //res = res.Erode(element);
                    res = res.Dilate(element);

                    window2.ShowImage(res);
                } else
                    break;
                
            }
            capture.Release();
        }
    }
}
