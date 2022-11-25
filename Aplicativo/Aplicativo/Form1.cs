namespace Aplicativo {
    public partial class Form1 : Form {

        private Bitmap img;
        public Form1() {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e) {
            OpenFileDialog op = new OpenFileDialog();
            op.Filter = "Imagen JPG|*.jpg|Imagen PNG|*.png|Imagen BMP|*.bmp|Todos los demas|*.*";
            op.FileName = String.Empty;
            var resp = op.ShowDialog();
            if (resp == DialogResult.OK) {
                img = new Bitmap(op.FileName);
                pictureBox1.Image = img;
                pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;
                Bitmap imgG = new Bitmap(img.Width, img.Height);

                for (int x = 0; x < img.Width; x++) {
                    for (int y = 0; y < img.Height; y++) {
                        var pixel = img.GetPixel(x, y);
                        var promedio = (pixel.R + pixel.G + pixel.B) / 3;
                        imgG.SetPixel(x, y, Color.FromArgb(pixel.A, promedio, promedio, promedio));
                    }
                }
                pictureBox2.Image = imgG;
                pictureBox2.SizeMode = PictureBoxSizeMode.Zoom;
            }
        }

        private void trackBar1_ValueChanged(object sender, EventArgs e) {
            var valor = trackBar1.Value;
            Bitmap img2 = new Bitmap(img.Width, img.Height);

            for (int x = 0; x < img.Width; x++) {
                for (int y = 0; y < img.Height; y++) {
                    var pixel = img.GetPixel(x, y);
                    int r, g, b;
                    if (valor < 0) {
                        r = pixel.R - ((valor * pixel.R) / trackBar1.Minimum);
                        g = pixel.G - ((valor * pixel.G) / trackBar1.Minimum);
                        b = pixel.B - ((valor * pixel.B) / trackBar1.Minimum);
                    } else {
                        r = pixel.R + ((valor * (255 - pixel.R)) / trackBar1.Maximum);
                        g = pixel.G + ((valor * (255 - pixel.G)) / trackBar1.Maximum);
                        b = pixel.B + ((valor * (255 - pixel.B)) / trackBar1.Maximum);
                    }
                    img2.SetPixel(x, y, Color.FromArgb(pixel.A, r, g, b));
                    pictureBox1.Image = img2;
                }
            }
        }

        private void trackBar2_ValueChanged(object sender, EventArgs e) {
            var valor = trackBar1.Value;
            Bitmap img2 = new Bitmap(img.Width, img.Height);

            for (int x = 0; x < img.Width; x++) {
                for (int y = 0; y < img.Height; y++) {
                    var pixel = img.GetPixel(x, y);
                    int r, g, b;
                    r = pixel.R + trackBar2.Value;
                    r = r > 255 ? 255 : r < 0 ? 0 : r;
                    g = pixel.G + trackBar2.Value;
                    g = g > 255 ? 255 : g < 0 ? 0 : g;
                    b = pixel.B + trackBar2.Value;
                    b = b > 255 ? 255 : b < 0 ? 0 : b;

                    img2.SetPixel(x, y, Color.FromArgb(pixel.A, r, g, b));
                    pictureBox1.Image = img2;
                }
            }
        }

        private void button2_Click(object sender, EventArgs e) {
            var valor = trackBar1.Value;
            Bitmap img2 = new Bitmap(img.Width, img.Height);
            Bitmap imgp = (Bitmap)pictureBox1.Image;
            for (int x = 0; x < img.Width; x++) {
                for (int y = 0; y < img.Height; y++) {
                    var pixel = imgp.GetPixel(x, y);
                    int r, g, b;
                    r = 255 - pixel.R;
                    g = 255 - pixel.G;
                    b = 255 - pixel .B;
                    img2.SetPixel(x, y, Color.FromArgb(pixel.A, r, g, b));
                    pictureBox1.Image = img2;
                }
            }
        }

        private void button3_Click(object sender, EventArgs e) {
            int n = 3;
            int[,] kernel = new int[n,n];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    kernel[i, j] = 1;
                }
            }
            
            Bitmap img2 = new Bitmap(img.Width, img.Height);
            Bitmap imgp = (Bitmap)pictureBox1.Image;
            for (int x = n/2; x < img.Width-(n/2); x++) {
                for (int y = n/2; y < img.Height-(n/2); y++) {
                    int r = 0, g = 0, b = 0;
                    int xk = 0, yk = 0;
                    for (int i = x-(n/2); i <= x+(n/2); i++) {
                        yk = 0;
                        for (int j = y- (n / 2); j <= y+ (n / 2); j++) {
                            var pixel = imgp.GetPixel(i, j);
                            r += (pixel.R * kernel[xk, yk]);
                            g += (pixel.G * kernel[xk, yk]);
                            b += (pixel.B * kernel[xk, yk]);

                            yk++;
                        }
                        xk++;
                    }
                    r /= n*n;
                    g /= n*n;
                    b /= n*n;

                    img2.SetPixel(x, y, Color.FromArgb(imgp.GetPixel(x, y).A, 
                        r < 0 ? 0 : r > 255 ? 255: r,
                        g < 0 ? 0 : g > 255 ? 255 : g,
                        b < 0 ? 0 : b > 255 ? 255 : b));
                    
                }
            }
            pictureBox2.Image = img2;
        }

        private void button4_Click(object sender, EventArgs e) {
            int n = 3;
            int[,] kernel = new int[n, n];
            
            kernel[0, 0] = 1;
            kernel[0, 1] = 2;
            kernel[0, 2] = 1;
            kernel[1, 0] = 2;
            kernel[1, 1] = 4;
            kernel[1, 2] = 2;
            kernel[2, 0] = 1;
            kernel[2, 1] = 2;
            kernel[2, 2] = 1;

            Bitmap img2 = new Bitmap(img.Width, img.Height);
            Bitmap imgp = (Bitmap)pictureBox1.Image;
            for (int x = n / 2; x < img.Width - (n / 2); x++) {
                for (int y = n / 2; y < img.Height - (n / 2); y++) {
                    int r = 0, g = 0, b = 0;
                    int xk = 0, yk = 0;
                    for (int i = x - (n / 2); i <= x + (n / 2); i++) {
                        yk = 0;
                        for (int j = y - (n / 2); j <= y + (n / 2); j++) {
                            var pixel = imgp.GetPixel(i, j);
                            r += (pixel.R * kernel[xk, yk]);
                            g += (pixel.G * kernel[xk, yk]);
                            b += (pixel.B * kernel[xk, yk]);

                            yk++;
                        }
                        xk++;
                    }
                    r /= 16;
                    g /= 16;
                    b /= 16;

                    img2.SetPixel(x, y, Color.FromArgb(imgp.GetPixel(x, y).A,
                        r < 0 ? 0 : r > 255 ? 255 : r,
                        g < 0 ? 0 : g > 255 ? 255 : g,
                        b < 0 ? 0 : b > 255 ? 255 : b));

                }
            }
            pictureBox2.Image = img2;
        }

        private void button5_Click(object sender, EventArgs e) {
            var valor = trackBar1.Value;
            int n = 3;
            int[,] kernel = new int[n, n];
            kernel[0, 0] = 0;
            kernel[0, 1] = -1;
            kernel[0, 2] = 0;
            kernel[1, 0] = -1;
            kernel[1, 1] = 5;
            kernel[1, 2] = -1;
            kernel[2, 0] = 0;
            kernel[2, 1] = -1;
            kernel[2, 2] = 0;

            Bitmap img2 = new Bitmap(img.Width, img.Height);
            Bitmap imgp = (Bitmap)pictureBox1.Image;
            for (int x = n / 2; x < img.Width - (n / 2); x++) {
                for (int y = n / 2; y < img.Height - (n / 2); y++) {
                    int r = 0, g = 0, b = 0;
                    int xk = 0, yk = 0;
                    for (int i = x - (n / 2); i <= x + (n / 2); i++) {
                        yk = 0;
                        for (int j = y - (n / 2); j <= y + (n / 2); j++) {
                            var pixel = imgp.GetPixel(i, j);
                            r += (pixel.R * kernel[xk, yk]);
                            g += (pixel.G * kernel[xk, yk]);
                            b += (pixel.B * kernel[xk, yk]);

                            yk++;
                        }
                        xk++;
                    }

                    img2.SetPixel(x, y, Color.FromArgb(imgp.GetPixel(x, y).A,
                        r < 0 ? 0 : r > 255 ? 255 : r,
                        g < 0 ? 0 : g > 255 ? 255 : g,
                        b < 0 ? 0 : b > 255 ? 255 : b));

                }
            }
            pictureBox2.Image = img2;
        }
    }
}