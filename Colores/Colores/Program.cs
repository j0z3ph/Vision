using OpenCvSharp;

namespace Colores {
    internal class Program {
        static void Main(string[] args) {
            using VideoCapture video = new VideoCapture(0);
            using Window ventana1 = new Window("BGR");
            using Window ventana2 = new Window("HSV");
            using Window ventana3 = new Window("MASK");
            using Window ventana4 = new Window("SETTINGS");


            Cv2.CreateTrackbar("Hmin", "SETTINGS", 180);
            Cv2.CreateTrackbar("Smin", "SETTINGS", 255);
            Cv2.CreateTrackbar("Vmin", "SETTINGS", 255);

            Cv2.CreateTrackbar("Hmax", "SETTINGS", 180);
            Cv2.CreateTrackbar("Smax", "SETTINGS", 255);
            Cv2.CreateTrackbar("Vmax", "SETTINGS", 255);

            Cv2.SetTrackbarPos("Hmin", "SETTINGS", 0);
            Cv2.SetTrackbarPos("Smin", "SETTINGS", 0);
            Cv2.SetTrackbarPos("Vmin", "SETTINGS", 0);

            Cv2.SetTrackbarPos("Hmax", "SETTINGS", 180);
            Cv2.SetTrackbarPos("Smax", "SETTINGS", 255);
            Cv2.SetTrackbarPos("Vmax", "SETTINGS", 255);

            while (Cv2.WaitKey(30) != 27) {
                using Mat img = new Mat();
                video.Read(img);
                using Mat img2 = img.CvtColor(ColorConversionCodes.BGR2HSV);
                ventana1.ShowImage(img);
                ventana2.ShowImage(img2);
                var hmin = Cv2.GetTrackbarPos("Hmin", "SETTINGS");
                var smin = Cv2.GetTrackbarPos("Smin", "SETTINGS");
                var vmin = Cv2.GetTrackbarPos("Vmin", "SETTINGS");
                var hmax = Cv2.GetTrackbarPos("Hmax", "SETTINGS");
                var smax = Cv2.GetTrackbarPos("Smax", "SETTINGS");
                var vmax = Cv2.GetTrackbarPos("Vmax", "SETTINGS");

                Vec3i low = new Vec3i(hmin, smin, vmin);
                Vec3i high = new Vec3i(hmax, smax, vmax);
                using Mat mask = img2.InRange(low, high);
                ventana3.ShowImage(mask);

            }
        }
    }
}