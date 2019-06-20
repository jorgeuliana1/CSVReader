
# CSVReader - An easy-to-use object-oriented csv reader.

## Changelog

### Version 1.0.0. (Current) (Initial Release)

1. C++ version released.

### TODO / Future versions

1. Release Java version.

## Logistics

This library works in the following way:

1. CSVReader declaration.
1. Line is stored in the cache.
1. Specific information from the stored line is taken.
1. You do whatever you want with that information.

## Installation

### C++

Just drag-n-drop the CSVReader.cpp and CSVReader.h files to your project directory and the folowing line at the beggining of your code:

``` c++
#include "CSVReader.h"
```

Alternatively, if you are going to insert the files in some directory use:

``` c++
#include "your_directory/CSVReader.h"
```

## Usage

### Declaration

Just declare an _CSVReader_ object passing the csv file path, the separator pattern _regex_ and a boolean value confirming if the target file has a header or not.

**Example:**

foo/bar/foobar.csv contains:

``` csv
Artist,Genre
The Beetown,Rock
Nylon & Gargamel,Folk
Tob Stiffler,Folk Rock
King,Rock
```

``` c++
using namespace csv_reader;

CSVReader csv("foo/bar/foobar.csv", ",", true);
```

The CSVReader will interpretate the file in the following way:

Artist | Genre
-------|------
The Beetown | Rock
Nylon & Gargamel | Folk
Tob Stiffler | Folk Rock
King | Rock

Now, if you initialize the CSVReader in the following way:

``` c++
CSVReader csv("foo/bar/foobar.csv", ";", true);
```

You will get the following table:

Artist,Genre |
-------------|
The Beetown,Rock|
Nylon & Gargamel,Folk|
Tob Stiffler,Folk Rock|
King,Rock|

And, if you use in the following way:

``` c++
CSVReader csv("foo/bar/foobar.csv", ",", false);
```

You will get:

0 | 1
-------|------
Artist | Genre
The Beetown | Rock
Nylon & Gargamel | Folk
Tob Stiffler | Folk Rock
King | Rock

### Getting the next line

To get the next line you just have to

``` c++
csv.next();
```

But I sincerely recommend you to do this

``` c++
if(!csv.eof())
    csv.next();
```

The reason for it is that if you don't check if you reached the end of the file you probably will keep repeating the last line infinitely if you are using a loop, for example.

Now, let's suppose that we have a CSVReader for the foobar.csv as mentioned above, we are reading it, we haven't read any line yet, so we call the ***next()*** function checking if there is next line and everything.

Artist | Genre
-------|------
**The Beetown** | **Rock**
Nylon & Gargamel | Folk
Tob Stiffler | Folk Rock
King | Rock

The highlighted line above represents the current cached line on the ***CSV*** object.
Then we do it once again to reach the second line.

Artist | Genre
-------|------
The Beetown | Rock
**Nylon & Gargamel** | **Folk**
Tob Stiffler | Folk Rock
King | Rock

You can notice that if you want to reach the row 7 from a just initialized CSVReader you just need to call ***next()*** 7 times. And for 8, 9, 10 and 1 billion the rule is the same. That's how simple it is.

### Getting the wanted element

Now we are just one step away from getting an specific element from a _**.csv**_ file.
In order to achieve that we only need to call the _**getFromCachedLine()**_ function.

``` c++
string myFavoriteGenre;
myFavoriteGenre = csv.getFromCachedLine("Genre");
```

As you must remember, the last line we picked was the second row from the _**foobar.csv**_ file and we activated the header reading, so we can just type "Genre" as parameter instead of counting index by index, subtracting one value and reading one more line in order to find the exact position of the "Nylon & Gargamel" class "Genre". ~~(Or we could just read it by eyes and write on a paper)~~. As expected, we are going to obtain the string "Folk Rock" as output.

### Finally

Well, what I was trying to tell this whole time is that you only need to type:

``` c++
#include <stdio>
#include "CSVReader.h"

using namespace std;

int main {

    CSVReader csv("foo/bar/foobar.csv", ",", true);

    for(int i = 0; i < 2 && !csv.eof(); i++)
        csv.next();

    string myFavoriteGenre = csv.getFromCachedLine("Genre");
    std::cout << myFavoriteGenre << endl;

    return 0;
}
```

To tell the whole world ~~or only your terminal~~ that Folk is your favorite genre.

You can even search by artist/group name:

``` c++
#include <stdio>
#include "CSVReader.h"

using namespace std;

int main {

    CSVReader csv("foo/bar/foobar.csv", ",", true);

    String favoriteArtist = "Nylon & Gargamel";
    int difference = -1;

    // Searching for the artist name.
    while(!csv.eof() && difference) {
        csv.next();
        string artist = csv.getFromCachedLine("Artist");
        difference = artist.compare(favoriteArtist);
    }

    string myFavoriteGenre = csv.getFromCachedLine("Genre");
    std::cout << myFavoriteGenre << endl;

    return 0;
}
```

Hope it is useful for you! See you soon!

Library kindly brought to you by @jorgeuliana1. :heart_eyes_cat:
