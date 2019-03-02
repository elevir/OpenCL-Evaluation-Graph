using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CLGraph;

namespace TestOpenCLLib
{
    class Program
    {
        static int Main(string[] args)
        {
            var devices = Device.GetAllDevices();
            foreach (var device in devices)
	        {
                Console.WriteLine(device.GetId());
                Console.WriteLine(device.GetDeviceType());
            }

            var cpuDevice = devices.LastOrDefault(device => device.GetDeviceType() == Device.DeviceType.GPU);
            if (cpuDevice == null)
            {
                Console.Error.WriteLine("No needed device");
                return -1;
            }
            // construct graph
            Data data1 = new Data(
                new[] {
                    1.0f, -2.0f,
                    3.0f, 4.0f, }, 
                new[] { 2ul, 2ul });
            Data data2 = new Data(
                new[] {
                    5.0f, 6.0f,
                    -7.0f, 8.0f, },
                new[] { 2ul, 2ul });
            Data scalar = new Data(9.0f);
            Console.WriteLine(data1);
            Console.WriteLine(data2);
            Console.WriteLine(scalar);
            var add_node = Node.AddNode(data1, data2, cpuDevice);
            var add_scalar = Node.AddNode(add_node, scalar, cpuDevice);
            // get result
            var add_result = add_scalar.Evaluate();

            // output result
            Console.WriteLine($"A matrix:{Environment.NewLine}{data1}");
            Console.WriteLine("+");
            Console.WriteLine($"B matrix:{Environment.NewLine}{data2}");
            Console.WriteLine("=");
            Console.WriteLine($"C matrix:{Environment.NewLine}{add_result}");
            Console.WriteLine();

            var elem_wise_mul = Node.ElementWiseMulNode(data1, data2, cpuDevice);
            var elem_wise_scalar = Node.ElementWiseMulNode(elem_wise_mul, scalar, cpuDevice);

            var elem_wise_result = elem_wise_scalar.Evaluate();

            // output result
            Console.WriteLine($"A matrix:{Environment.NewLine}{data1}");
            Console.WriteLine(".*");
            Console.WriteLine($"B matrix:{Environment.NewLine}{data2}");
            Console.WriteLine("=");
            Console.WriteLine($"C matrix:{Environment.NewLine}{elem_wise_result}");
            Console.WriteLine();

            var abs_data1 = Node.AbsNode(data1, cpuDevice);
            var abs_data2 = Node.AbsNode(data2, cpuDevice);

            var abs_data1_result = abs_data1.Evaluate();
            var abs_data2_result = abs_data2.Evaluate();

            Console.WriteLine($"abs(A) matrix:{Environment.NewLine}{abs_data1_result}");
            Console.WriteLine($"abs(B) matrix:{Environment.NewLine}{abs_data2_result}");

            var sqrt_data1 = Node.SqrtNode(data1, cpuDevice);
            var sqrt_data2 = Node.SqrtNode(data2, cpuDevice);

            var sqrt_data1_result = sqrt_data1.Evaluate();
            var sqrt_data2_result = sqrt_data2.Evaluate();

            Console.WriteLine($"sqrt(A) matrix:{Environment.NewLine}{sqrt_data1_result}");
            Console.WriteLine($"sqrt(B) matrix:{Environment.NewLine}{sqrt_data2_result}");
            return 0;
        }
    }
}
