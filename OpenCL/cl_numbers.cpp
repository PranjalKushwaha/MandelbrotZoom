#include <math.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include "./utility.cpp"
#include <chrono>

#define height 1000
#define width 1000
cl_float zoom = 1;
using namespace std;
static const cl_uint vectorSize = 4096; //must be evenly divisible by workSize
static const cl_uint workSize = 512;

int main(void)
{
	using std::chrono::duration;
	using std::chrono::high_resolution_clock;
	using std::chrono::seconds;

	cl_int err;
	std::vector<cl::Platform> PlatformList;

	err = cl::Platform::get(&PlatformList);
	checkErr(err, "Get Platform List");
	checkErr(PlatformList.size() >= 1 ? CL_SUCCESS : -1, "cl::Platform::get");
	print_platform_info(&PlatformList);

	uint current_platform_id = get_platform_id_with_string(&PlatformList, "Emulation");
	printf("Using Platform: %d\n\n", current_platform_id);

	std::vector<cl::Device> DeviceList;

	err = PlatformList[current_platform_id].getDevices(CL_DEVICE_TYPE_ALL, &DeviceList);
	checkErr(err, "Get Devices");
	print_device_info(&DeviceList);

	cl::Context mycontext(DeviceList, NULL, NULL, NULL, &err);
	checkErr(err, "Context Constructor");

	cl::CommandQueue myqueue(mycontext, DeviceList[0], 0, &err);
	checkErr(err, "Queue Constructor");

	cl::Buffer Buffer_Out(mycontext, CL_MEM_WRITE_ONLY, sizeof(cl_int) * sizeof(cl_int) * width * height, NULL, &err);
	cl::Buffer Zoom(mycontext, CL_MEM_READ_ONLY, sizeof(cl_float), NULL, &err);

	string file_path = "./kernel.cl";
	string clcode = "";
	string item_name;
	ifstream file;

	file.open(file_path);
	vector<cl::string> f;
	while (!file.eof())
	{
		getline(file, item_name);
		clcode += item_name;
		f.push_back(item_name);
	}
	myqueue.enqueueWriteBuffer(Zoom, false, 0, sizeof(cl_float), &zoom, NULL, NULL);
	myqueue.finish();

	cl::Program program = cl::Program(mycontext, clcode);

	err = program.build(DeviceList[0]);
	cout << "Error : " << err << endl;
	if (err == -11)
	{
		for (cl::Device dev : DeviceList)
		{
			// Check the build status
			cl_build_status status = program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(dev);
			if (status != CL_BUILD_ERROR)
				continue;

			// Get the build log
			std::string name = dev.getInfo<CL_DEVICE_NAME>();
			std::string buildlog = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(dev);
			std::cerr << "Build log for " << name << ":" << std::endl
					  << buildlog << std::endl;
		}
	}

	cl::Kernel kernel(program, "num_gen");
	kernel.setArg(0, Zoom);

	kernel.setArg(1, Buffer_Out);
	cl::NDRange global(height*width);
	//cl::NDRange local(vectorSize / 8, vectorSize / 8, 1);
	auto t1 = high_resolution_clock::now();

	myqueue.enqueueNDRangeKernel(kernel, cl::NDRange(), global);
	myqueue.finish();
	cl_int* count = new cl_int[height*width];
	myqueue.enqueueReadBuffer(Buffer_Out, false, 0, sizeof(cl_int) * sizeof(cl_int) * height*width, count, NULL, NULL);
	myqueue.finish();

	auto t2 = high_resolution_clock::now();
	duration<double> ms_double = t2 - t1;
	for (int i = 0; i < height*width; i++)
	{
		cout << count[i] << endl;
	}
}
