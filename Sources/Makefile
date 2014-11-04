##  Makefile
##
## Copyright (c) 2014 Sébastien MICHOY
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are met:
##
## Redistributions of source code must retain the above copyright notice, this
## list of conditions and the following disclaimer. Redistributions in binary
## form must reproduce the above copyright notice, this list of conditions and
## the following disclaimer in the documentation and/or other materials
## provided with the distribution. Neither the name of the nor the names of
## its contributors may be used to endorse or promote products derived from
## this software without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
## IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
## ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
## LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
## CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
## SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
## INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
## CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
## POSSIBILITY OF SUCH DAMAGE.

# Set project name
OUT     = SortingAlgorithmsBinary

# Set path configuration
INCDIR  = SortingAlgorithms/
SRCDIR  = SortingAlgorithms/
OBJDIR  = SortingAlgorithms/

# Set commands
CC		= @gcc
RM      = @rm -f

# Set compilation flags
CFLAGS  = -W -Wall -Wextra -Wstrict-prototypes

# Getting files in directories
INC     = $(notdir $(wildcard $(INCDIR)*.h))
SRC     = $(notdir $(wildcard $(SRCDIR)*.c))
OBJ     = $(notdir $(SRC:.c=.o))

# Setting paths for prerequisites
VPATH   = $(SRCDIR) $(OBJDIR) $(INCDIR)

# Setting default target (i.e. project name)
$(OUT)  : $(OBJ)
        #@echo "- linking of: $@"
	$(CC) -lm $(addprefix $(OBJDIR), $(OBJ)) -o $@

# Rewritting objects compilation rule
%.o     : %.c $(INC)
	@echo "- compilation of: $@"
	$(CC) -c $(addprefix $(SRCDIR), $(@:.o=.c)) -o $(addprefix $(OBJDIR), $@) -I $(INCDIR) $(CFLAGS) 

# Generals targets
all     : $(OUT)

clean   :
	@echo "- cleaning objects directory"
	$(RM) $(addprefix $(OBJDIR), $(OBJ))
	$(RM) $(INCDIR)*~
	$(RM) $(SRCDIR)*~

fclean  : clean
	@echo "- erasing project: $(OUT)"
	$(RM) @rm -f $(OUT)

re      : fclean all

