# Get_Next_Line
The aim of this  42 project is to make us code a function that returns a line, read from a file descriptor.

# Context:

# Understanding File Reading Line by Line: A Simple Guide

## What is a File Descriptor?

Think of a file descriptor as a ticket number that your computer gives you when you want to read or write to something. Just like how a ticket helps identify your coat at a coat check, a file descriptor helps your program keep track of what file or input stream it's working with.

When your program starts, it automatically gets three special ticket numbers. Number 0 lets you read from the keyboard (standard input), number 1 lets you write to the screen (standard output), and number 2 is for error messages (standard error). Any other files you open will get numbers starting from 3.

## How Reading Actually Works

When your program wants to read from a file, it uses something called the read() function. This function is like a person scooping water from a river into a bucket. The file descriptor tells it which river (file) to scoop from, and you also tell it how big your bucket (buffer) is.

The interesting thing about read() is that it doesn't understand words or sentences - it just grabs raw data, like scooping water without caring if you're cutting through a wave. Sometimes you might ask it to get 100 bytes, but it might only give you 50 if that's all that's immediately available. It will tell you exactly how many bytes it managed to get.

When read() reaches the end of the file, it lets you know by returning zero, like hitting the bottom of an empty pool. If something goes wrong (like trying to read from a file that was closed), it tells you by returning a negative number.

## Understanding Line Reading

Reading a line might seem simple - just get everything until you see a newline character (\n), right? But it's trickier than it looks. Here's why:

When you scoop data from a file, you might get a chunk that starts in the middle of one line and ends in the middle of another. Or you might get several complete lines at once. Or you might get just part of a line with no ending in sight.

That's why you need to be smart about how you handle the data. You need to keep track of any partial lines you've read and combine them with new data until you have a complete line. It's like putting together a puzzle, but the pieces arrive one handful at a time.

## The Line Reading Process

First, you check if you have any leftover data from your last read. This is like checking if there's still some soup in your bowl before getting more from the pot.

Then, if you need more data, you read some from the file. You add this new data to any leftovers you had, like adding more soup to what was already in your bowl.

Next, you look through what you have, searching for a newline character. If you find one, great! Everything up to that point (including the newline) becomes your line to return. Anything after it gets saved for next time.

If you don't find a newline, you'll need to read more data and try again. This continues until either you find a newline or reach the end of the file.

## Handling Special Cases

Sometimes you'll run into special situations. What if someone gives you an invalid file descriptor? That's like trying to scoop water from a river that doesn't exist - you need to handle that error gracefully.

What if you reach the end of the file in the middle of a line? Most people expect that last line to be returned even if it doesn't end with a newline character.

What if someone gives you a huge file with very long lines? You need to be able to handle that without running out of memory or getting confused about where you are in the file.

## Being Efficient

The trick to making this work well is to be smart about when you read from the file. You don't want to read one character at a time - that would be like making hundreds of trips to the river with a tiny cup. But you also don't want to read huge chunks if you don't need them - that would be like bringing a swimming pool's worth of water when you just need a glass.

You also need to be careful with memory. Every time you store data or create a new string, you're using up memory. If you're not careful about cleaning up after yourself, your program will start using more and more memory until it becomes a problem.

## Testing Your Work

When you're done writing your function, you need to test it thoroughly. Try reading from normal files, from the keyboard, from empty files. Try reading files with long lines, short lines, no newlines at all. Try reading with different buffer sizes.

Each of these tests might reveal different problems you need to fix. It's like testing a soup recipe - you need to make sure it tastes good whether you make a small batch or a large one, whether you serve it hot or cold, whether you use fresh ingredients or frozen ones.


# The Algorithm

# Understanding Get Next Line: A Simple Code Explanation

## The Main Function: get_next_line

Think of get_next_line as a librarian who helps you read a book one line at a time. This librarian uses a special bookmark (we call it 'stash') to remember where they left off between visits. When you ask for a line, the librarian does three main things: reads until they find a complete line, gives you that line, and updates their bookmark for next time.

The librarian first checks if you've given them a valid book (fd) and if they're allowed to read a reasonable amount at a time (BUFFER_SIZE). If either of these is wrong, they'll politely tell you they can't help (return NULL).

## Reading Until We Find a Line

The read_to_line function works like someone reading a book with their finger. They keep reading and collecting text (in their stash) until they either find the end of a line (marked by '\n') or reach the end of the book.

They use a small notepad (buffer) to read chunks of text at a time. After each chunk is read, they add it to their collection (stash) and check if they've found the end of a line. If they ever have trouble reading (bytes_read is -1), they throw away their notepad (free buffer) and let you know there's a problem.

For example, if they read "Hello" first, then "World\n", their stash will end up containing "HelloWorld\n". They keep doing this until they either find a '\n' or reach the end of the book.

## Extracting the Line

The extract_line function is like using scissors to carefully cut out the first line from our collected text. First, it measures how long the line is by counting characters until it hits either a newline ('\n') or the end of the text.

If we have "HelloWorld\n" in our stash, it will count the length (11 characters including the '\n'), create a new piece of paper exactly that size (plus one for '\0'), and carefully copy just that line over. It's like cutting "HelloWorld\n" from a larger piece of paper that might have more text below it.

## Cleaning Up the Stash

The clean_stash function is like updating our bookmark after we've read a line. If our original stash had "HelloWorld\nGoodbye", after extracting "HelloWorld\n", we need to keep "Goodbye" for next time.

First, it finds where the first line ends (after the '\n'). Then it makes a new stash with just the remaining text. It's like taking a new piece of paper and copying everything that comes after the line we just read. If there's nothing left after our line (no more text), it throws away the stash entirely (returns NULL).

It's similar to moving your bookmark to the start of the next line after you've finished reading the current one.

## The Whole Process Together

Let's say someone asks to read a file containing "Hello\nWorld\n" line by line:

1. First call:
   - read_to_line reads until it has "Hello\nWorld\n"
   - extract_line gives back "Hello\n"
   - clean_stash keeps "World\n" for next time

2. Second call:
   - read_to_line sees we already have "World\n", so it doesn't need to read more
   - extract_line gives back "World\n"
   - clean_stash finds nothing left, so it clears the stash

3. Third call:
   - read_to_line tries to read more but finds nothing (end of file)
   - returns NULL since there's nothing left to read

The static stash is like the librarian's memory - it remembers where we left off between visits, making sure we don't lose any text and don't read the same line twice.



# Resources
https://www.gnu.org/software/libc/manual/html_node/Processes.html#:~:text=A%20process%20executes%20a%20program,independently%20of%20the%20other%20copies.&text=The%20processes%20created%20by%20a%20given%20parent%20are%20called%20its%20child%20processes. <br />
https://www.geeksforgeeks.org/memory-layout-of-c-program/ <br />
https://stackoverflow.com/questions/14042824/where-is-open-max-defined-for-linux-systems <br />
https://www.geeksforgeeks.org/what-is-memory-leak-how-can-we-avoid/ <br />
https://man7.org/linux/man-pages/man2/open.2.html <br />
https://prezi.com/4mhun2mlbssd/get-next-line/ <br />
https://www.ibm.com/docs/en/xl-c-and-cpp-linux/16.1.0?topic=iod--1 <br />
https://www.tutorialspoint.com/cprogramming/c_preprocessors.htm <br />
https://jameshfisher.com/2017/02/22/ssize_t/ <br />
https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/ <br />
https://velog.io/@ljiwoo59/getnextline <br />
https://www.educative.io/answers/what-is-a-buffer-in-c <br />
https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/ <br />
https://www.educba.com/macros-in-c/
