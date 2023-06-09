#include <stdio.h>
#include <Python.h>

/**
include <stdio.h>
VIEW HEADER-> https://www.gnu.org/software/m68hc11/examples/stdio_8h-source.html
VIEW MANUAL-> https://man7.org/linux/man-pages/man0/stdio.h.0p.html
include <Python.h>
VIEW HEADER-> https://stackoverflow.com/questions/21530577/fatal-error-python-h-no-such-file-or-directory
VIEW MANUAL-> https://docs.python.org/3/c-api/intro.html
 * print_python_bytes - Prints bytes of information.
 *
 * @p: Python Object.
 * Return: No return.
 */
void print_python_bytes(PyObject *p)
{
	char *string;
	long int size, i, Limit;

	printf("[.] bytes object info\n");
	if (!PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	size = ((PyVarObject *)(p))->ob_size;
	string = ((PyBytesObject *)p)->ob_sval;

	printf("  size: %ld\n", size);
	printf("  trying string: %s\n", string);

	if (size >= 10)
		Limit = 10;
	else
		Limit = size + 1;

	printf("  first %ld bytes:", Limit);

	for (i = 0; i < Limit; i++)
		if (string[i] >= 0)
			printf(" %02x", string[i]);
		else
			printf(" %02x", 256 + string[i]);

	printf("\n");
}

/**
 * print_python_list - Prints list information.
 *
 * @p: Python Object.
 * Return: No return.
 */
void print_python_list(PyObject *p)
{
	long int size, i;
	PyListObject *list;
	PyObject *obj;

	size = ((PyVarObject *)(p))->ob_size;
	list = (PyListObject *)p;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", list->allocated);

	for (i = 0; i < size; i++)
	{
		obj = ((PyListObject *)p)->ob_item[i];
		printf("Element %ld: %s\n", i, ((obj)->ob_type)->tp_name);
		if (PyBytes_Check(obj))
			print_python_bytes(obj);
	}
}

