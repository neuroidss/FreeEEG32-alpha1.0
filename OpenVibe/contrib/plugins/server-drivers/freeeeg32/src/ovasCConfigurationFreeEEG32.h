/*
 * FreeEEG32 driver for OpenViBE
 *
 * \author Jeremy Frey
 *
 * \note Based on OpenEEG code; inherits its AGPL3 license conditions
 *
 */
#ifndef __OpenViBE_AcquisitionServer_CConfigurationFreeEEG32_H__
#define __OpenViBE_AcquisitionServer_CConfigurationFreeEEG32_H__

#include "../ovasCConfigurationBuilder.h"

#include <gtk/gtk.h>

namespace OpenViBEAcquisitionServer
{
	class CConfigurationFreeEEG32 : public OpenViBEAcquisitionServer::CConfigurationBuilder
	{
	public:
		CConfigurationFreeEEG32(const char* sGtkBuilderFileName, OpenViBE::uint32& rUSBIndex);
		virtual ~CConfigurationFreeEEG32(void);

		virtual OpenViBE::boolean preConfigure(void);
		virtual OpenViBE::boolean postConfigure(void);
		
		OpenViBE::boolean setComInit(const OpenViBE::CString& sComInit);
		OpenViBE::CString getComInit(void) const;
		
		OpenViBE::boolean setComDelay(const OpenViBE::uint32 iComDelay);
		OpenViBE::uint32 getComDelay(void) const;
		
		OpenViBE::boolean setDaisyModule(const OpenViBE::boolean sDaisyModule);
		OpenViBE::boolean getDaisyModule(void) const;
		

	protected:
		OpenViBE::uint32& m_rUSBIndex;
		::GtkListStore* m_pListStore;
		::GtkEntry* l_pEntryComInit;
		OpenViBE::CString m_sComInit;
		OpenViBE::uint32 m_iComDelay;
		OpenViBE::boolean m_bDaisyModule;
	};
};

#endif // __OpenViBE_AcquisitionServer_CConfigurationFreeEEG32_H__
