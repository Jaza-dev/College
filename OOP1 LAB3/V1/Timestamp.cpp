#include "Timestamp.h"

ostream& operator<< (ostream& os, const Timestamp& ts) {
	return os << ts.day << "." << ts.month << "." << ts.year << "-" << ts.hour << ":" << ts.minute;
}
