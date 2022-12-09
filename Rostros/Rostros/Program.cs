using OpenCvSharp;
using System.Numerics;

namespace Rostros {
    internal class Program {
        static void Main(string[] args) {
            using Window ventana = new Window("Caras");
            //using Window ventana2 = new Window("cara");
            using VideoCapture cam = new VideoCapture(0);
            using Mat img = new Mat();
            using Mat gris = new Mat();
            using CascadeClassifier cascada = new CascadeClassifier(@"haarcascades\haarcascade_frontalface_alt2.xml");
            //using CascadeClassifier cascadaojos = new CascadeClassifier(@"haarcascades\haarcascade_eye_tree_eyeglasses.xml");

            using Mat lentes = Cv2.ImRead( @"img\lentes2.png", ImreadModes.Unchanged);
            using Mat mustache = Cv2.ImRead(@"img\mustache2.png", ImreadModes.Unchanged);
            int key;
            bool showGlasses = false;
            bool showMustache = false;

            while ((key = Cv2.WaitKey(30)) != 27) {
                cam.Read(img);
                Cv2.CvtColor(img, gris, ColorConversionCodes.BGR2GRAY);
                Cv2.EqualizeHist(gris, gris);
                Rect[] caras = cascada.DetectMultiScale(gris, 1.1, 3);
                foreach (var cara in caras) {
                    //using Mat c = gris[cara];
                    //using Mat c2 = c.Resize(new Size(c.Width*2, c.Height*2));
                    //using Mat cc = img[cara];
                    //Rect[] ojos = cascadaojos.DetectMultiScale(c);
                    //foreach (var ojo in ojos) {
                    //    cc.Circle(new Point((ojo.X) + (ojo.Width / 2), (ojo.Y) + (ojo.Height / 2)), ojo.Width / 4, new Scalar(0, 255, 0), 3);
                    //cc.Rectangle(ojo, new Scalar(0, 255, 0), 3);
                    //}

                    if (key == 'g') showGlasses = !showGlasses;
                    if (key == 'm') showMustache = !showMustache;
                    
                    if(showGlasses) {
                        using Mat tmp = lentes.Resize(new Size(cara.Width, cara.Height * 0.2));
                        Mat mask;
                        Mat[] layers;

                        Cv2.Split(tmp, out layers);
                        mask = layers[3];
                        Mat[] rgb = { layers[0], layers[1], layers[2] };
                        Cv2.Merge(rgb, tmp);

                        tmp.CopyTo(img[new Rect(cara.X, (int)(cara.Y + (cara.Height * 0.3)),
                            tmp.Width, tmp.Height)], mask);
                        mask.Dispose();
                        layers[0].Dispose();
                        layers[1].Dispose();
                        layers[2].Dispose();
                        layers[3].Dispose();
                        rgb[0].Dispose();
                        rgb[1].Dispose();
                        rgb[2].Dispose();

                    }

                    if (showMustache) {
                        using Mat tmp = mustache.Resize(new Size(cara.Width*0.8, cara.Height * 0.2));
                        Mat mask;
                        Mat[] layers;
                        
                        Cv2.Split(tmp, out layers);
                        mask = layers[3];
                        Mat[] rgb = { layers[0], layers[1], layers[2] };
                        Cv2.Merge(rgb, tmp);

                        tmp.CopyTo(img[new Rect((int)(cara.X + (cara.Width * 0.1)), (int)(cara.Y + (cara.Height * 0.65)),
                            tmp.Width, tmp.Height)], mask);
                        mask.Dispose();
                        layers[0].Dispose();
                        layers[1].Dispose();
                        layers[2].Dispose();
                        layers[3].Dispose();
                        rgb[0].Dispose();
                        rgb[1].Dispose();
                        rgb[2].Dispose();

                    }
                    //img.Rectangle(cara, new Scalar(255, 0, 0), 5);
                }
                ventana.ShowImage(img);
                
            }
        }
    }
}