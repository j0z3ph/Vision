using OpenCvSharp;

namespace Faces {
    internal class Program {
        static void Main(string[] args) {
            using Window window = new Window("Video");
            using VideoCapture video = new VideoCapture(0);
            using Mat image = new Mat();
            using CascadeClassifier haarCascade = new CascadeClassifier(@"C:\src\progavan\Vision\haarcascades\haarcascade_frontalface_alt2.xml");

            while (Cv2.WaitKey(30) != 27) {
                video.Read(image);
                using Mat gray = image.CvtColor(ColorConversionCodes.BGR2GRAY);
                Rect[] faces = haarCascade.DetectMultiScale(gray);
                foreach (var face in faces) {
                    image.Rectangle(face, new Scalar(0,255,0));
                }
                window.ShowImage(image);
            }

        }
    }
}