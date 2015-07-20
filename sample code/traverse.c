//Open up the superblock free list and read the inodes

#include "ext2_types.h"
#include "ext2fs.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>

struct ext2_super_block getSuperblock (struct ext2_super_block * superblock, char* device){
	int reader;
	char boot[1024];

	reader = open(device, O_RDONLY);
	
	if ( reader < 0 ) {
		printf("Opening %s failed\n", device);
		printf ("Error number is : %d\n", errno);
		printf("Error description is : %s\n",strerror(errno));
		exit (0);
	} else {
		printf("Opening %s succeeded\n", device);
	}
	
	/* Reads the boot section and the superblock */
	read(reader, boot, 1024);
	read(reader, superblock, sizeof(struct ext2_super_block));
	close(reader);
}

int getGroupTableStart (struct ext2_super_block * superblock){
	int groupCount = getGroupCount(superblock);
	int blockSize = EXT2_BLOCK_SIZE(superblock);
	//load all group descriptors into memory:
	
	printf("Found %d groups\n", groupCount);
	printf("Block size: %d\n", blockSize);
	
	//Groups always begin in block following superblock, so need to check how far forwards to seek
	int groupsBlockOffset = ceilDiv(blockSize, SUPERBLOCK_SIZE)*blockSize + SUPERBLOCK_OFFSET;
	return groupsBlockOffset;
}

inline int ceilDiv(int a, int b){
	return (a+b -1)/b;
}

int getGroupCount (struct ext2_super_block * superblock){
	int num_blocks = superblock->s_blocks_count;
	int num_inodes = superblock->s_inodes_count;
	int blocks_per_group = EXT2_BLOCKS_PER_GROUP(superblock);
	int inodes_per_group = EXT2_INODES_PER_GROUP(superblock);
	
	//Round up and verify answer two ways
	int answer_a = ceilDiv(num_blocks, blocks_per_group);
	int answer_b = ceilDiv(num_inodes, inodes_per_group);
	
	assert (answer_a == answer_b);
	return answer_a;
}

struct ext2_group_desc ** getGroups (struct ext2_super_block * superblock){
	int blockSize = EXT2_BLOCK_SIZE(superblock);
	int groupsBlockOffset = ceilDiv(blockSize, SUPERBLOCK_SIZE)*blockSize + SUPERBLOCK_OFFSET;
}

int main (){
	struct ext2_super_block * superblock = malloc (sizeof (struct ext2_super_block));
	getSuperblock(superblock, "/dev/sda3");
	
	printf("Loaded superblock for %s\n", superblock->s_volume_name);
	
	int groupCount;
	struct ext2_group_desc ** groups;
	
	 = getGroupCount(superblock);
	int blockSize = EXT2_BLOCK_SIZE(superblock);
	//load all group descriptors into memory:
	
	printf("Found %d groups\n", groupCount);
	printf("Block size: %d\n", blockSize);
	
	//Groups always begin in block following superblock, so need to check how far forwards to seek
	
	
	printf("Seeking forwards %d find groups\n", groupsBlockOffset);
	
	//Read all of the groups and find which ones contain files to restore
	
	
	//Now need to get the groups:

	/*lseek(reader, firstFree, SEEK_CUR);
	
	struct ext2_inode node;
	read(reader, &node, sizeof(struct ext2_inode));
	printf("i_size is %d\n", node.i_size);
	printf("i_links_count is %d\n", node.i_links_count);
	printf("i_blocks is %d\n", node.i_blocks);
	printf("i_flags is %#016x\n", node.i_flags);
	
	struct stat stats;
	
	stat("/home/karl/code/3430a3/sample code/data/test", &stats);
	printf("File size is %ld\n", stats.st_size);
	printf("Inode location is %ld\n", stats.st_ino);

	close(reader);
	*/
	printf("Processing Completed\n");
	return 0;
}
