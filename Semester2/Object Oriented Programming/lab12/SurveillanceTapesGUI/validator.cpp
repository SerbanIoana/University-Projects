#include "validator.h"

string TapeValidator::validate_date(const Date & date)
{
	string errors;
	if (date.get_day() < 0 || date.get_day() > 31)
		errors += string("Invalid day for date!\n");
	if (date.get_month() < 0 || date.get_month() > 12)
		errors += string("Invalid month for date!\n");
	if (date.get_year() < 0)
		errors += string("Invalid year for date!\n");
	return errors;
}

void TapeValidator::validate_tape(const Tape & tape)
{
	string errors;

	if (tape.get_title().size() < 1)
		errors += string("The title cannot be less than 1 character!\n");

	if (tape.get_filmedAt().size() < 1)
		errors += string("The filmedAt cannot be less than 1 character\n");

	errors += validate_date(tape.get_creationDate());

	if (tape.get_accessCount() < 0)
		errors += string("The accessCount cannot be negative\n");

	if (tape.get_footagePreview().size() < 1)
		errors += string("The foootage preview cannot be less than 1 character!\n");
	
	if (errors.size() > 0)
		throw Exception(errors);
}
