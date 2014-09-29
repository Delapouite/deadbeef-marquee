# copy those in ./local/bin/deadbeef
OUT_GTK2?=ddb_marquee_gtk2.so
OUT_GTK3?=ddb_marquee_gtk3.so

# flags
GTK2_CFLAGS?=`pkg-config --cflags gtk+-2.0`
GTK3_CFLAGS?=`pkg-config --cflags gtk+-3.0`
LIBXML2_CFLAGS?=`pkg-config --cflags libxml-2.0`

# libs
GTK2_LIBS?=`pkg-config --libs gtk+-2.0`
GTK3_LIBS?=`pkg-config --libs gtk+-3.0`
LIBXML2_LIBS?=`pkg-config --libs libxml-2.0`

CC?=gcc
CFLAGS+=-Wall -fPIC -std=c99 -D_GNU_SOURCE
LDFLAGS+=-shared

# dirs
GTK2_DIR?=gtk2
GTK3_DIR?=gtk3

# sources
SOURCES?=$(wildcard *.c)
OBJ_GTK2?=$(patsubst %.c, $(GTK2_DIR)/%.o, $(SOURCES))
OBJ_GTK3?=$(patsubst %.c, $(GTK3_DIR)/%.o, $(SOURCES))

define compile
	$(CC) $(CFLAGS) $1 $2 $< -c -o $@
endef

define link
	$(CC) $(LDFLAGS) $1 $2 $3 -o $@
endef


# builds both GTK+2 and GTK+3 versions of the plugin
all: gtk2 gtk3

# builds GTK+2 version of the plugin
gtk2: mkdir_gtk2 $(SOURCES) $(GTK2_DIR)/$(OUT_GTK2)

# builds GTK+3 version of the plugin
gtk3: mkdir_gtk3 $(SOURCES) $(GTK3_DIR)/$(OUT_GTK3)

mkdir_gtk2:
	@echo "Creating build directory for GTK+2 version"
	@mkdir -p $(GTK2_DIR)

mkdir_gtk3:
	@echo "Creating build directory for GTK+3 version"
	@mkdir -p $(GTK3_DIR)

$(GTK2_DIR)/$(OUT_GTK2): $(OBJ_GTK2)
	@echo "Linking GTK+2 version"
	@$(call link, $(OBJ_GTK2), $(LIBXML2_LIBS), $(GTK2_LIBS))
	@echo "Done!"

$(GTK3_DIR)/$(OUT_GTK3): $(OBJ_GTK3)
	@echo "Linking GTK+3 version"
	@$(call link, $(OBJ_GTK3), $(LIBXML2_LIBS), $(GTK3_LIBS))
	@echo "Done!"

$(GTK2_DIR)/%.o: %.c
	@echo "Compiling $(subst $(GTK2_DIR)/,,$@)"
	@$(call compile, $(LIBXML2_CFLAGS), $(GTK2_CFLAGS))

$(GTK3_DIR)/%.o: %.c
	@echo "Compiling $(subst $(GTK3_DIR)/,,$@)"
	@$(call compile, $(LIBXML2_CFLAGS), $(GTK3_CFLAGS))

clean:
	@echo "Cleaning files from previous build..."
	@rm -r -f $(GTK2_DIR) $(GTK3_DIR)
