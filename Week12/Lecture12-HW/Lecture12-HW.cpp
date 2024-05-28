#include <iostream>
#include <chrono>
#include <thread>

int main(void)
{

	using namespace std::chrono;
	constexpr seconds interval(1);  // 1초 간격

	auto next_frame = steady_clock::now() + interval;

	while (true)
	{
		auto start = steady_clock::now();

		// 다음 프레임 시간까지 대기
		std::this_thread::sleep_until(next_frame);
		next_frame += interval;

		auto end = steady_clock::now();
		auto elapsed = duration_cast<milliseconds>(end - start);
		std::cout << "Elapsed time for loop: " << elapsed.count() << " ms" << std::endl;
	}
	return 0;
}
