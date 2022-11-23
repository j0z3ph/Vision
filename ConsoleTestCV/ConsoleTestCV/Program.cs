using OpenCvSharp;
using System.Security.Cryptography;

namespace ConsoleTestCV {
    internal class Program {
        static void Main(string[] args) {
            using VideoCapture capture = new VideoCapture(0);
            using Window window = new Window("Settings");
            using Window window2 = new Window("Filter");
            using Window window3 = new Window("Final");

            using Mat image = new Mat();
            Vec3i lower = new Vec3i();
            Vec3i upper = new Vec3i();
            using Mat element = Cv2.GetStructuringElement(MorphShapes.Ellipse, new Size(15, 15));

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
                    using Mat im1 = image.GaussianBlur(new Size(5, 5), 6);
                    using Mat im2 = im1.BilateralFilter(15, 100, 100);
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
                    
                    
                    using Mat maskt = hsv.InRange(lower, upper);
                    Mat res = new Mat();
                    using Mat mask = new Mat();

                    Cv2.Erode(maskt, mask, element);
                    Cv2.Dilate(mask, mask, element);
                    //Mat[] contours;
                    
                    

                    //mask.FindContours(out contours, OutputArray.Create(new Mat()), RetrievalModes.Tree, ContourApproximationModes.ApproxSimple);
                    
                    
                    Cv2.BitwiseAnd(image, image, res, mask);
                    //res = res.Erode(element);
                    //res = res.Dilate(element);
                    //foreach (var contour in contours) {
                        var rect = mask.BoundingRect();
                        image.Rectangle(rect, new Scalar(0, 255, 0));
                    //}
                    

                    window2.ShowImage(res);
                    window3.ShowImage(image);
                } else
                    break;
                
            }
            capture.Release();
        }
    }
}
