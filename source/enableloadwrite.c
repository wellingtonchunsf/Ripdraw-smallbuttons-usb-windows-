/* 
 * enableloadwrite()
 * 
 * 
 * 
 */
#include "../include/ripdraw.h"
#include "../include/sampleloader.h"

int layerstatus[8] = 
{
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE, \
	RD_FALSE \
};

int enableloadwrite(RD_INTERFACE* rd_interface, struct image_object local, int enableflag, int load_option, int write_option)
{
	extern int layerstatus[];
	int ret;
	int id_image;
	int id_imagewrite;

	/* Manipulate layer on incoming image object based on icoming enableflag and current status
	 * If current layer is off (RD_FALSE) and enablflage is true, enable layer, layer has not been enabled yet
	 * if current layer is on  (RD_TRUE) and enableflag is true, layer is already enable, skip and don't enable again
	 * if current layer is on  (RD_TURE and enableflage is false, disable layer
	 */

	ret = STATUS_OK; /* set ret status to ok incase we don't do anything */

	if (((layerstatus[local.image_layer] == RD_FALSE) && (enableflag)) ||   ((!enableflag) && ((layerstatus[local.image_layer]== (RD_TRUE)))))
	{
		printf("\nLayer %d status %d", local.image_layer, enableflag);
	        layerstatus[local.image_layer] = enableflag;		/* set status to layer based on flag */ 
		ret = Rd_SetLayerEnable(rd_interface, local.image_layer, enableflag); /* enable or disable based on incoming flag layer only once for each layer */
		if (ret != STATUS_OK) return ret;
	}

	/* load image if load_option is selected */
	if (load_option)
	{
		/* Load image based on incoming image object  */
		printf("\nLoading image %s", local.image_name);
		ret = Rd_ImageLoad(rd_interface, local.image_name, &id_image);
		if (ret != STATUS_OK) return ret;
		local.image_id = id_image;   /* store image_id from Rd_ImageLoad backinto object*/
	}

	/* write image if write_option is selected */
	if (write_option)
	{
		/* Write the image based on the incoming image object */
		printf("\nImagewrite");
		ret = Rd_ImageWrite(rd_interface,local.image_layer,id_image, Rd_Position(local.image_x, local.image_y), &id_imagewrite);
		if (ret != STATUS_OK) return ret;
		local.image_write_id = id_imagewrite;   /* store image_id from Rd_ImageLoad backinto object*/
	}

	return ret;
}
