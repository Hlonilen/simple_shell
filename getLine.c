#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_val *info, char **buf, size_t *len)
{
	ssize_t valrun = 0;
	size_t lenpin = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		valrun = getline(buf, &lenpin, stdin);
#else
		valrun = _getline(info, buf, &lenpin);
#endif
		if (valrun > 0)
		{
			if ((*buf)[valrun - 1] == '\n')
			{
				(*buf)[valrun - 1] = '\0'; /* remove trailing newline */
				valrun--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = valrun;
				info->cmd_buf = buf;
			}
		}
	}
	return (valrun);
}

/**
 * get_input - receives a line without the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_val *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t valin, valjun, len;
	ssize_t valrun = 0;
	char **buf_p = &(info->arg), *valpin;

	_putchar(BUF_FLUSH);
	valrun = input_buf(info, &buf, &len);
	if (valrun == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		valjun = valin; /* init new iterator to current buf position */
		valpin = buf + valin; /* get pointer for return */

		check_chain(info, buf, &valjun, valin, len);
		while (valjun < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &valjun))
				break;
			valjun++;
		}

		valin = valjun + 1; /* increment past nulled ';'' */
		if (valin >= len) /* reached end of buffer? */
		{
			valin = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = valpin; /* return the reference to the current command position */
		return (_strlen(valpin)); /* return the current command's length */
	}

	*buf_p = buf; /* If there is no chain, return the buffer from _getline() */
	return (valrun); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @valin: size
 *
 * Return: valrun
 */
ssize_t read_buf(info_val *info, char *buf, size_t *valin)
{
	ssize_t valrun = 0;

	if (*valin)
		return (0);
	valrun = read(info->readval, buf, READ_BUF_SIZE);
	if (valrun >= 0)
		*valin = valrun;
	return (valrun);
}

/**
 * _getline - STDIN's next line of input is retrieved.
 * @info: parameter struct
 * @pota: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated pota buffer if not NULL
 *
 * Return: valsum
 */
int _getline(info_val *info, char **pota, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t valin, len;
	size_t valkin;
	ssize_t valrun = 0, valsum = 0;
	char *valpin = NULL, *new_p = NULL, *valcum;

	valpin = *pota;
	if (valpin && length)
		valsum = *length;
	if (valin == len)
		valin = len = 0;

	valrun = read_buf(info, buf, &len);
	if (valrun == -1 || (valrun == 0 && len == 0))
		return (-1);

	valcum = _strchr(buf + valin, '\n');
	valkin = valcum ? 1 + (unsigned int)(valcum - buf) : len;
	new_p = _realloc(valpin, valsum, valsum ? valsum + valkin : valkin + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (valpin ? free(valpin), -1 : -1);

	if (valsum)
		_strncat(new_p, buf + valin, valkin - valin);
	else
		_strncpy(new_p, buf + valin, valkin - valin + 1);

	valsum += valkin - valin;
	valin = valkin;
	valpin = new_p;

	if (length)
		*length = valsum;
	*pota = valpin;
	return (valsum);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
