#include <sys/mman.h>                /* mmap()                        */
#include <sys/types.h>				 /* open() , fstat()              */
#include <sys/stat.h> 				 /* open() , fstat()              */

#include <fcntl.h> 		             /* open close 	*/

#include <stdio.h>
#include <stdlib.h>         
#include <string.h>		             /* memcpy 		*/
#include <unistd.h>		             /* close 		*/

#include </home/xyz/.local/share/Trash/files/rpi-tools/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/arm-linux-gnueabihf/libc/usr/include/linux/ext2_fs.h> 

#define BLOCK_SIZE  (1024)
#define BASE_OFFSET (1024)

#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*BLOCK_SIZE)

int main(void)
{
	int i, j;
	int fd;
	/* struct stat file_status = {0};*/
	unsigned char *map_ptr = NULL;	/* Pointer to mmap source file 	*/
	unsigned char* ptr;
	struct ext2_super_block super_block;
	struct ext2_group_desc gdt;
	struct ext2_inode inode_table;
	struct ext2_dir_entry_2 dir_entry;
	int inode_table_offset;
	unsigned char *reader ;
	
	
	fd = open("/dev/ram0",O_RDONLY);
	if (-1 == fd)
	{
		fputs("failed to open file\n",stderr);
		return 1;
	}

	map_ptr = (unsigned char *)mmap(NULL, 4000*1024, PROT_READ, 
						   MAP_PRIVATE ,fd, 0);
	if(MAP_FAILED == map_ptr)
	{
		fputs("mmap failed\n",stderr);
		
		close(fd);
		return 1;	
	}
	
	
	/* Reads the boot section and the superblock */
	ptr = map_ptr;
	ptr +=BLOCK_SIZE ; /* skip boot section */
	memcpy(&super_block, ptr, sizeof(struct ext2_super_block));
	
	if (super_block.s_magic != EXT2_SUPER_MAGIC)
	{
		fputs("failed locate super block\n",stderr);
		
		close(fd);
		return 1;
	}
			
	/* Group Descriptors  */
	ptr += BLOCK_SIZE; /* skip super block */
	memcpy(&gdt, ptr, sizeof(struct ext2_group_desc));
	
	printf("block: %d\n", gdt.bg_block_bitmap); 
	printf("inode: %d\n", gdt.bg_inode_bitmap);
	printf("table: %d\n", gdt.bg_inode_table);
	printf("first ino: %d\n",super_block.s_first_ino);
	printf("sizeof inode: %lu\n",sizeof(struct ext2_inode));
	
/*	inode_table_offset = super_block.s_first_ino ; */
	inode_table_offset = gdt.bg_inode_table ; 
	
	ptr = map_ptr; /* go to start */
	ptr += BLOCK_OFFSET(inode_table_offset); /* point to the first inode */
	ptr += sizeof(struct ext2_inode); /* skip inode to the second */
	
	
	memcpy(&inode_table, ptr, sizeof(struct ext2_inode));
	
	printf ("i_mode: %x\n",inode_table.i_mode);
	
	if (S_ISDIR(inode_table.i_mode))
	{
		puts ("its dir");
	}
	printf ("i_block: %d\n",inode_table.i_block[0]);
	
	ptr = map_ptr; /* go to start */
	ptr += BLOCK_OFFSET(inode_table.i_block[0]);
	
	memcpy(&dir_entry, ptr, sizeof(struct ext2_dir_entry_2));
	printf("dir name: %s\n", dir_entry.name);  /* dir : . */
	printf("rec len: %d\n", dir_entry.rec_len);
	
	ptr += dir_entry.rec_len;

	memcpy(&dir_entry, ptr, sizeof(struct ext2_dir_entry_2));
	printf("dir name: %s\n", dir_entry.name);  /* dir : .. */
	printf("rec len: %d\n", dir_entry.rec_len);
	
	ptr += dir_entry.rec_len;
	
	memcpy(&dir_entry, ptr, sizeof(struct ext2_dir_entry_2));
	printf("dir name: %s\n", dir_entry.name);  /* dir : lost+found */
	printf("rec len: %d\n", dir_entry.rec_len);
	
	ptr += dir_entry.rec_len;
	
	memcpy(&dir_entry, ptr, sizeof(struct ext2_dir_entry_2));
	for (i = 0; i < dir_entry.name_len ; ++i ) /* file : 1.txt */
	{
		printf("%c", dir_entry.name[i]);
	}
	printf("\n");
	printf("file inode: %d\n", dir_entry.inode);

	ptr = map_ptr; /* go to start */
	ptr += BLOCK_OFFSET(inode_table_offset); /* point to the first inode */
	ptr += (dir_entry.inode -1 )* sizeof(struct ext2_inode); /* skip to the requested inode */
	
	memcpy(&inode_table, ptr, sizeof(struct ext2_inode));
	if (S_ISREG(inode_table.i_mode))
	{
		puts ("its file");
		
	}
	printf("num of blocks (for file): %d\n", (inode_table.i_blocks));


	/* go to file location and read it */
	printf("file content:\n");
	for (i = 0; i < inode_table.i_blocks ; ++i ) /* file : 1.txt */
	{
		reader  = map_ptr;
		reader += BLOCK_OFFSET(inode_table.i_block[i]);
		for (j = 0; (j < BLOCK_SIZE) && (*reader != EOF); ++j)
		{
			printf("%c", reader[j]);
		}
		
	}
	
	
	
	close(fd);
	return 0;
}
