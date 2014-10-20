using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
delegate void ShowAction(List<int> dividers, int of_what);
namespace factorize
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

        private void Factorize(int what)
		{
            int val = what;
			List<int> dividers = new List<int>();
            bool flag;
            while (what > 1)
            {
                flag = true;
                int div = (int)Math.Sqrt(what);
                for (int i = 2; i <= div; i++)
                {
                    if (what % i == 0)
                    {
                        what = what / i;
                        dividers.Add(i);
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    dividers.Add(what);
                    break;
                }
             
            }
//too fast..
            Thread.Sleep(10000);
            ShowAction action = ShowSuc;
			this.Invoke(action, new Object[] {dividers,val});
      
		}

		private void ShowSuc(List<int> dividers, int ofWhat)
		{
			this.listBox1.Items.Add(string.Format("{0} = {1}", ofWhat, string.Join("*",	dividers)));
		}

		private void Show(string fail)
		{
			this.listBox1.Items.Add(fail);
		}

		private void button1_Click(object sender, EventArgs e)
		{
			if (textBox1.Text == "") return;
			string num = textBox1.Text;
			textBox1.Text = "";

			int val;
			if (int.TryParse(num, out val))
			{
//some Thread magic
                Thread worker = new Thread(()=>Factorize(val));
                worker.Start();
			}
			else
			{
				Show(num + " is NaN");
			}
		}
	}
}
