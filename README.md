# Movie Catalog

## 1. Introduction

This is a small CLI application to organize movies on a catalog.

Movies contain a name, production company and are rated.

The catalog has a fixed size and is persisted into a CSV file.

Developed by Mario Simão for the Programming Languages class, during the Computer
and Electronic Engineering course at the Federal University of Rio de Janeiro (UFRJ).

## 2. Compilation

To compile, execute:

```bash
$ make all
```

## 3. Usage

```bash
$ ./catalog help
```

or

```bash
$ ./catalog <catalog-name> <command> [<args>]
```

Where `<catalog-name>` should be the name of your catalog.

More information about available commands are given below.

### 3.1. help

Displays information about all commands.

```bash
$ ./catalog help
```

### 3.2. create

Creates a new catalog and its corresponding CSV file.

**Warning:** This is a destructive command. If a catalog with same name already
exists, it will be deleted and a new one will be created.

```bash
$ ./catalog <catalog-name> create <size>
```

Example:

```bash
$ ./catalog my-movies create 100
```

The application will create a catalog with capacity for 100 movies.

Also, a `my-movies.csv` file will be created on the same directory.

### 3.3. add

Inserts a movie into the catalog. Prompt asking for movie information.

```bash
$ ./catalog <catalog-name> add
```

Example:

```bash
$ ./catalog my-movies add
```

will prompt for movie information:

```
Add movie to catalog
* Name: Harry Potter
* Production: Warner Bros
* Rating: 8.9
```

### 3.4. bulk-add

Inserts multiple movies into the catalog. The amount of movies should be informed
previously. The application will prompt multiple times asking for movie information.

```bash
$ ./catalog <catalog-name> bulk-add <amount-of-movies>
```

```bash
$ ./catalog my-movies bulk-add 5
```

Will prompt 5 times asking for movie data.

### 3.5. list

Lists all movies inside the catalog.

```bash
$ ./catalog <catalog-name> list
```

### 3.6. search

Searches for a movie. Shows an error message if the movie was not found.

```bash
$ ./catalog <catalog-name> search <movie-name>
```

Example

```bash
$ ./catalog my-movies search "Harry Potter"
```

### 3.7. best

Find the movie with the highest rating.

```bash
$ ./catalog <catalog-name> best
```

### 3.8. rename

Rename a movie.

```bash
$ ./catalog <catalog-name> rename <old-name> <new-name>
```

Example:

```bash
$ ./catalog my-movies rename "Harry Poter" "Harry Potter"
```

### 3.9. update-production

Updates a movie production.

```bash
$ ./catalog <catalog-name> update-production <movie-name> <new-production>
```

Example:

```bash
$ ./catalog my-movies update-production "Harry Potter" "Warner"
```

### 3.10. update-rating

Updates a movie rating.

```bash
$ ./catalog <catalog-name> update-rating <movie-name> <new-rating>
```

Example:

```bash
$ ./catalog my-movies update-production "Harry Potter" 9.4
```

### 3.11. remove

Removes a movie from the catalog.

```bash
$ ./catalog <catalog-name> remove <movie-name>
```

Example:

```bash
$ ./catalog my-movies remove "Harry Potter"
```
