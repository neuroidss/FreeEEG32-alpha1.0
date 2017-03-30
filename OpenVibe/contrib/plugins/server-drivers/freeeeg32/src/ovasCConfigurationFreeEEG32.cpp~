/*
 * FreeSmartEEG driver for OpenViBE
 *
 * \author Jeremy Frey
 *
 * \note Based on OpenEEG code; inherits its AGPL3 license conditions
 *
 */
#include "ovasCConfigurationFreeSmartEEG.h"

using namespace OpenViBE;
using namespace OpenViBE::Kernel;
using namespace OpenViBEAcquisitionServer;

CConfigurationFreeSmartEEG::CConfigurationFreeSmartEEG(const char* sGtkBuilderFileName, OpenViBE::uint32& rUSBIndex)
	:CConfigurationBuilder(sGtkBuilderFileName)
	,m_rUSBIndex(rUSBIndex)
{
	m_pListStore=gtk_list_store_new(1, G_TYPE_STRING);
}

CConfigurationFreeSmartEEG::~CConfigurationFreeSmartEEG(void)
{
	g_object_unref(m_pListStore);
}

boolean CConfigurationFreeSmartEEG::preConfigure(void)
{
	if(!CConfigurationBuilder::preConfigure())
	{
		return false;
	}

	::GtkEntry* l_pEntryComInit=GTK_ENTRY(gtk_builder_get_object(m_pBuilderConfigureInterface, "entry_com_init"));
	::gtk_entry_set_text(l_pEntryComInit, m_sComInit.toASCIIString());

	::GtkSpinButton* l_pSpinButtonComDelay=GTK_SPIN_BUTTON(gtk_builder_get_object(m_pBuilderConfigureInterface, "spinbutton_com_delay"));
	::gtk_spin_button_set_value(l_pSpinButtonComDelay, m_iComDelay);
	
	::GtkToggleButton* l_pToggleButtonDaisyModule=GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_pBuilderConfigureInterface, "checkbutton_daisy_module"));
	::gtk_toggle_button_set_active(l_pToggleButtonDaisyModule, m_bDaisyModule?true:false);
		
	::GtkComboBox* l_pComboBox=GTK_COMBO_BOX(gtk_builder_get_object(m_pBuilderConfigureInterface, "combobox_device"));

	g_object_unref(m_pListStore);
	m_pListStore=gtk_list_store_new(1, G_TYPE_STRING);

	gtk_combo_box_set_model(l_pComboBox, GTK_TREE_MODEL(m_pListStore));

	char l_sBuffer[1024];
	boolean l_bSelected=false;

	for(uint32 i=1; i<27; i++)
	{
#if defined TARGET_OS_Windows
		::sprintf(l_sBuffer, "\\\\.\\COM%i", i);
#elif defined TARGET_OS_Linux
		if(i<10)
		{
			::sprintf(l_sBuffer, i<10?"/dev/ttyS%d":"/dev/ttyUSB%d", i);
		}
		else
		if(i<20)
		{
			::sprintf(l_sBuffer, "/dev/ttyUSB%d", i-10);
		}
		else
		{
			::sprintf(l_sBuffer, "/dev/ttyACM%d", i-20);
		}
#else
		::sprintf(l_sBuffer, "");
#endif
		::gtk_combo_box_append_text(l_pComboBox, l_sBuffer);
		if(m_rUSBIndex==i)
		{
			::gtk_combo_box_set_active(l_pComboBox, i-1);
			l_bSelected=true;
		}
	}

	if(!l_bSelected)
	{
		::gtk_combo_box_set_active(l_pComboBox, 0);
	}

	return true;
}

boolean CConfigurationFreeSmartEEG::postConfigure(void)
{
	::GtkComboBox* l_pComboBox=GTK_COMBO_BOX(gtk_builder_get_object(m_pBuilderConfigureInterface, "combobox_device"));

	if(m_bApplyConfiguration)
	{
		int l_iUSBIndex=gtk_combo_box_get_active(l_pComboBox);
		if(l_iUSBIndex>=0)
		{
			m_rUSBIndex=(uint32)l_iUSBIndex+1;
		}
		
		::GtkEntry* l_pEntryComInit=GTK_ENTRY(gtk_builder_get_object(m_pBuilderConfigureInterface, "entry_com_init"));
		m_sComInit=::gtk_entry_get_text(l_pEntryComInit);
		
		::GtkSpinButton* l_pSpinButtonComDelay=GTK_SPIN_BUTTON(gtk_builder_get_object(m_pBuilderConfigureInterface, "spinbutton_com_delay"));
		gtk_spin_button_update(GTK_SPIN_BUTTON(l_pSpinButtonComDelay));
		m_iComDelay=::gtk_spin_button_get_value_as_int(l_pSpinButtonComDelay);
		
		::GtkToggleButton* l_pToggleButtonDaisyModule=GTK_TOGGLE_BUTTON(gtk_builder_get_object(m_pBuilderConfigureInterface, "checkbutton_daisy_module"));
		m_bDaisyModule=::gtk_toggle_button_get_active(l_pToggleButtonDaisyModule)?true:false;	
	}

	if(!CConfigurationBuilder::postConfigure())
	{
		return false;
	}
	return true;
}

boolean CConfigurationFreeSmartEEG::setComInit(const CString& sComInit)
{
        m_sComInit=sComInit;
        return true;
}


CString CConfigurationFreeSmartEEG::getComInit(void) const
{
        return m_sComInit;
}

boolean CConfigurationFreeSmartEEG::setComDelay(uint32 iComDelay)
{
        m_iComDelay=iComDelay;
        return true;
}


uint32 CConfigurationFreeSmartEEG::getComDelay(void) const
{
        return m_iComDelay;
}

bool CConfigurationFreeSmartEEG::setDaisyModule(bool bDaisyModule)
{
        m_bDaisyModule=bDaisyModule;
        return true;
}


bool CConfigurationFreeSmartEEG::getDaisyModule(void) const
{
        return m_bDaisyModule;
}
