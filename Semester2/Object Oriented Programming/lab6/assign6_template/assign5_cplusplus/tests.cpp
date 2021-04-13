#include "tape.h"
#include "dynamicVector.h"
#include "repository.h"
#include "service.h"
#include <iostream>
#include <cassert>


void tapeConstructor_ValidInput_Created()
{
	Tape();
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };
	assert(tape.get_title() == "aaa");
}

void dynamicVectorConstructor_ValidInput_Created()
{
	DynamicVector<Tape>();
	DynamicVector<Tape> dynamicVector{ 10 };
	Tape element;
	dynamicVector.add(element);
	assert(dynamicVector.get_size() == 1);
}

void dynamicVectorCopyConstructor_ValidInput_Created()
{
	DynamicVector<Tape>();
	DynamicVector<Tape> dynamicVector{ 10 };
	DynamicVector<Tape> dynamicVector2{ 10 };
	Tape element;
	dynamicVector2.add(element);
	dynamicVector = dynamicVector2;
	assert(dynamicVector.get_size() == 1);
}

void dynamicVector_add_ValidInput_Added()
{
	DynamicVector<Tape>();
	DynamicVector<Tape> dynamicVector{ 10 };
	Tape element;
	dynamicVector.add(element);
	assert(dynamicVector[0].get_title() == element.get_title());
}

void dynamicVector_update_ValidInput_Updated()
{
	DynamicVector<Tape>();
	DynamicVector<Tape> dynamicVector{ 10 };
	Tape element;
	Tape element2;
	dynamicVector.add(element);
	dynamicVector.update(1, element2);
	assert(element.get_title() == element2.get_title());
}

void dynamicVector_delete_ValidInput_Deleted()
{
	DynamicVector<Tape>();
	DynamicVector<Tape> dynamicVector{ 10 };
	Tape element;
	dynamicVector.add(element);
	dynamicVector.remove(1);
	assert(dynamicVector.get_size() == 0);
}

void repositoryConstructor_ValidInput_Created()
{
	DynamicVector<Tape>();
	DynamicVector<Tape> dynamicVector{ 10 };
	Repository repo{};
	assert(repo.get_sizeRepository() == 0);
}

void repository__add_tape__ValidInput__Added()
{
	DynamicVector<Tape>();
	DynamicVector<Tape> dynamicVector{ 10 };
	Repository repo{};
	Tape();
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };
	repo.add_tape(tape);
	assert(repo.get_sizeRepository() == 1);
}

void repository__update_tape__ValidInput__Updated()
{
	DynamicVector<Tape>();
	DynamicVector<Tape> dynamicVector{ 10 };
	Repository repo{};
	Tape();
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };
	repo.add_tape(tape);
	Tape();
	Date date1{ 9,12,2019 };
	Tape tape1{ "aaa", "ABC", date1, 8, "ASD" };
	repo.update_tape(tape1);
	assert(repo.get_position_tape(0).get_filmedAt() == "ABC");
}

void repository__delete_tape__ValidInput__Deleted()
{
	DynamicVector<Tape>();
	DynamicVector<Tape> dynamicVector{ 10 };
	Repository repo{};
	Tape();
	Date date{ 9,12,2019 };
	Tape tape{ "aaa", "sss", date, 7, "ddd" };
	repo.add_tape(tape);
	Tape();
	Date date1{ 6,10,2019 };
	Tape tape1{ "bbb", "ABC", date1, 8, "ASD" };
	repo.add_tape(tape1);
	repo.delete_tape(tape.get_title());
	assert(repo.get_sizeRepository() == 1);
}

void serviceConstructor_ValidInput_Created()
{
	Repository repo{};
	Service service{ repo };
	assert(service.get_repository().get_sizeRepository() == 0);
}

void service__add_tape__ValidInput__Added()
{
	Repository repo{};
	Service service{ repo };
	Date date{ 9,12,2019 };
	int result = service.service_add_tape("aaa", "sss", date, 7, "ddd");
	assert(result == 1);
}

void service__add_tape__InvalidInput__Return0()
{
	Repository repo{};
	Service service{ repo };
	Date date{ 9,12,2019 };
	service.service_add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 5,11,2019 };
	int result = service.service_add_tape("aaa", "sss", date1, 7, "ddd");
	assert(result == 0);
}

void service_update_tape_ValidInput_Updated()
{
	Repository repo{};
	Service service{ repo };
	Date date{ 9,12,2019 };
	service.service_add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 5,11,2019 };
	int result = service.service_update_tape("aaa", "vvv", date1, 8, "www");
	assert(result == 1);
}

void service_update_tape_InvalidInput_Return0()
{
	Repository repo{};
	Service service{ repo };
	Date date{ 9,12,2019 };
	service.service_add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 5,11,2019 };
	int result = service.service_update_tape("bbb", "vvv", date1, 8, "www");
	assert(result == 0);
}

void service_delete_tape_ValidInput_Deleted()
{
	Repository repo{};
	Service service{ repo };
	Date date{ 9,12,2019 };
	service.service_add_tape("aaa", "sss", date, 7, "ddd");
	Date date1{ 5,11,2019 };
	service.service_add_tape("bbb", "vvv", date1, 8, "www");
	service.service_delete_tape("aaa");
	assert(service.get_repository().get_sizeRepository() == 1);
}

void service_delete_tape_InvalidInput_Return0()
{
	Repository repo{};
	Service service{ repo };
	Date date{ 9,12,2019 };
	service.service_add_tape("aaa", "sss", date, 7, "ddd");
	int result = service.service_delete_tape("bbb");
	assert(result == 0);
}

void test_all()
{
	tapeConstructor_ValidInput_Created();
	dynamicVectorConstructor_ValidInput_Created();
	dynamicVectorCopyConstructor_ValidInput_Created();
	dynamicVector_add_ValidInput_Added();
	dynamicVector_update_ValidInput_Updated();
	dynamicVector_delete_ValidInput_Deleted();

	repositoryConstructor_ValidInput_Created();
	repository__add_tape__ValidInput__Added();
	repository__update_tape__ValidInput__Updated();
	repository__delete_tape__ValidInput__Deleted();

	serviceConstructor_ValidInput_Created();
	service__add_tape__ValidInput__Added();
	service__add_tape__InvalidInput__Return0();
	service_update_tape_ValidInput_Updated();
	service_update_tape_InvalidInput_Return0();
	service_delete_tape_ValidInput_Deleted();
	service_delete_tape_InvalidInput_Return0();

	std::cout << "All tests done!";
}