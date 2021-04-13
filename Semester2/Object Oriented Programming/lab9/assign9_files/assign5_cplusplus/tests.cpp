#include "tape.h"
#include "fileRepository.h"
#include "repository.h"
#include "service.h"
#include <iostream>
#include <cassert>


void tape__constructor__ValidInput__Created()
{
	Tape();
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };
	assert(tape.get_title() == "aaa");
}

void date__constructor__ValidInput__Created()
{
	Date();
	Date date{ 9,12,2019 };
	assert(date.get_day() == 9);
}

void repository__constructor__ValidInput__Created()
{
	Repository repo{};
	assert(repo.get_size() == 0);
}

void repository__add_tape__ValidInput__Added()
{
	Repository repo{};
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };

	repo.add_tape(tape);
	assert(repo.get_tapes()[0].get_title() == "aaa");
}

void repository__update_tape__ValidInput__Updated()
{
	Repository repo{};
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };
	repo.add_tape(tape);
	Date date1{ 9,12,2019 };
	Tape tape1{ "aaa", "ABC", date1, 8, "ASD" };

	repo.update_tape(tape1);
	assert(repo.get_tapes()[0].get_filmedAt() == "ABC");
}

void repository__delete_tape__ValidInput__Deleted()
{
	Repository repo{};
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };
	repo.add_tape(tape);
	Date date1{ 6,10,2019 };
	Tape tape1{ "bbb", "ABC", date1, 8, "ASD" };
	repo.add_tape(tape1);

	repo.delete_tape(tape.get_title());
	assert(repo.get_tapes()[0].get_footagePreview() == tape1.get_footagePreview());
}

void repository__get_position_tape__ValidInput_ValidPosition()
{
	Repository repo{};
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };
	repo.add_tape(tape);

	int position = repo.get_position_tape(tape);
	assert(position == 0);
}

void repository__get_position_tape__InvalidInput_InvalidPosition()
{
	Repository repo{};
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };
	repo.add_tape(tape);
	Date date1{ 6,10,2019 };
	Tape tape1{ "bbb", "ttt", date1, 8, "eee" };

	int position = repo.get_position_tape(tape1);
	assert(position == -1);
}

void agentRepository__constructor__ValidInput__Created()
{
	AgentRepository agent_repo{};
	assert(agent_repo.get_agent_tapes().size() == 0);
}

void agentRepository__agent_add_tape__ValidInput__Added()
{
	AgentRepository agent_repo{};
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };

	agent_repo.agent_add_tape(tape);
	assert(agent_repo.get_agent_tapes()[0] == tape);
}

void service__constructor__ValidInput__Created()
{
	FileRepository repo{};
	Service service{ repo };
	assert(service.get_repository().get_size() == 0);
}

void service__add_tape__ValidInput__Return1()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	int result = service.add_tape("aaa", "sss", date, 7, "ddd");
	assert(result == 1);
	service.delete_tape("aaa");
}

void service__add_tape__InvalidInput__Return0()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	service.add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 5,11,2019 };
	int result = service.add_tape("aaa", "ccc", date1, 9, "fff");
	assert(result == 0);
	service.delete_tape("aaa");
}

void service__update_tape__ValidInput__Return1()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	service.add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 5,11,2019 };
	int result = service.update_tape("aaa", "vvv", date1, 8, "www");
	assert(result == 1);
	service.delete_tape("aaa");
}

void service__update_tape__InvalidInput__Return0()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	service.add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 5,11,2019 };
	int result = service.update_tape("bbb", "vvv", date1, 8, "www");
	assert(result == 0);
	service.delete_tape("aaa");
}

void service__delete_tape__ValidInput__Return1()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	service.add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 5,11,2019 };
	service.add_tape("bbb", "vvv", date1, 8, "www");
	int result = service.delete_tape("aaa");
	assert(result == 1);
	service.delete_tape("bbb");
}

void service__delete_tape__InvalidInput__Return0()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	service.add_tape("aaa", "sss", date, 7, "ddd");
	int result = service.delete_tape("bbb");
	assert(result == 0);
	service.delete_tape("aaa");
}

void service__get_filtered_by_filmedAt__ValidInput__ValidTapes()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	service.add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 9,3,2019 };
	service.add_tape("ccc", "ttt", date1, 9, "eee");
	Date date2{ 5,7,2019 };
	service.add_tape("bbb", "sss", date2, 8, "fff");

	vector<Tape> filtered_tapes = service.get_filtered_by_filmedAt("sss", 10);
	assert(filtered_tapes[1].get_creationDate() == date2);
	service.delete_tape("aaa");
	service.delete_tape("ccc");
	service.delete_tape("bbb");
}

void service__next_tape__ReturnTape()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	service.add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 9,3,2019 };
	service.add_tape("ccc", "ttt", date1, 9, "eee");
	Tape tape1{ "ccc", "ttt", date1, 9, "eee" };
	Date date2{ 5,7,2019 };
	service.add_tape("bbb", "sss", date2, 8, "fff");

	Tape next_tape = service.next_tape();
	next_tape = service.next_tape();
	assert(next_tape == tape1);
	service.delete_tape("aaa");
	service.delete_tape("ccc");
	service.delete_tape("bbb");
}

void service__save_tape__ValidInput__Saved()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	service.add_tape("aaa", "sss", date, 7, "ddd");

	service.save_tape("aaa");
	assert(service.get_agent_tapes()[0].get_footagePreview() == "ddd");
	service.delete_tape("aaa");
}

void service__save_tape__InvalidInput__Return0()
{
	FileRepository repo{};
	Service service{ repo };
	service.file_location("file_tests.txt");

	Date date{ 9,12,2019 };
	service.add_tape("aaa", "sss", date, 7, "ddd");

	int result = service.save_tape("bbb");
	assert(result == 0);
	service.delete_tape("aaa");
}

void fileRepository__add_tape__ValidInput__Added()
{
	FileRepository repo{};
	string file = "file_tests.txt";
	repo.set_file_location(file);

	Date date{ 9,3,2019 };
	Tape tape{ "ccc", "ttt", date, 9, "eee" };
	repo.add_tape(tape);
	
	assert(repo.search_by_title("ccc") == tape);
	repo.delete_tape("ccc");
}

void fileRepository__update_tape__ValidInput__Updated()
{
	FileRepository repo{};
	string file = "file_tests.txt";
	repo.set_file_location(file);

	Date date{ 9,3,2019 };
	Tape tape{ "ccc", "ttt", date, 9, "eee" };
	repo.add_tape(tape);
	Date date1{ 7,12,2019 };
	Tape tape1{ "ccc", "sss", date1, 10, "fff" };
	repo.update_tape(tape1);

	assert(repo.get_on_position(0).get_filmedAt() == "sss");
	repo.delete_tape("ccc");
}

void fileRepository__delete_tape__ValidInput__Deleted()
{
	FileRepository repo{};
	string file = "file_tests.txt";
	repo.set_file_location(file);

	Date date{ 9,3,2019 };
	Tape tape{ "ccc", "ttt", date, 9, "eee" };
	repo.add_tape(tape);
	Date date1{ 7,12,2019 };
	Tape tape1{ "bbb", "sss", date1, 10, "fff" };
	repo.add_tape(tape1);

	repo.delete_tape("ccc");
	assert(repo.get_on_position(0) == tape1);
	repo.delete_tape("bbb");
}

void fileRepository__search_by_title__ValidInput__Tape()
{
	FileRepository repo{};
	string file = "file_tests.txt";
	repo.set_file_location(file);

	Date date{ 9,3,2019 };
	Tape tape{ "ccc", "ttt", date, 9, "eee" };
	repo.add_tape(tape);

	Tape tape1 = repo.search_by_title("ccc");
	assert(tape == tape1);
	repo.delete_tape("ccc");
}

void fileRepository__search_by_title__InvalidInput__EmptyTape()
{
	FileRepository repo{};
	string file = "file_tests.txt";
	repo.set_file_location(file);

	Date date{ 9,3,2019 };
	Tape tape{ "ccc", "ttt", date, 9, "eee" };
	repo.add_tape(tape);

	Tape tape1 = repo.search_by_title("aaa");
	assert(tape1.get_title() == "Null");
	repo.delete_tape("ccc");
}

void test_all()
{
	tape__constructor__ValidInput__Created();
	date__constructor__ValidInput__Created();

	//normal repo
	repository__constructor__ValidInput__Created();
	repository__add_tape__ValidInput__Added();
	repository__update_tape__ValidInput__Updated();
	repository__delete_tape__ValidInput__Deleted();
	repository__get_position_tape__ValidInput_ValidPosition();
	repository__get_position_tape__InvalidInput_InvalidPosition();

	//agent repo
	agentRepository__constructor__ValidInput__Created();
	agentRepository__agent_add_tape__ValidInput__Added();

	//filerepo
	fileRepository__add_tape__ValidInput__Added(); //use ==
	fileRepository__update_tape__ValidInput__Updated();
	fileRepository__delete_tape__ValidInput__Deleted();
	fileRepository__search_by_title__ValidInput__Tape();
	fileRepository__search_by_title__InvalidInput__EmptyTape();

	//service
	service__constructor__ValidInput__Created();
	service__add_tape__ValidInput__Return1();
	service__add_tape__InvalidInput__Return0();
	service__update_tape__ValidInput__Return1();
	service__update_tape__InvalidInput__Return0();
	service__delete_tape__ValidInput__Return1();
	service__delete_tape__InvalidInput__Return0();
	service__get_filtered_by_filmedAt__ValidInput__ValidTapes();
	service__next_tape__ReturnTape();
	service__save_tape__ValidInput__Saved();
	service__save_tape__InvalidInput__Return0();

	std::cout << "All tests done!";
}