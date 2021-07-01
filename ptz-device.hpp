/* Pan Tilt Zoom device base object
 *
 * Copyright 2020 Grant Likely <grant.likely@secretlab.ca>
 *
 * SPDX-License-Identifier: GPLv2
 */
#pragma once

#include <memory>
#include <QDebug>
#include <QObject>
#include <QStringListModel>
#include <QtGlobal>
#include <obs.hpp>
#include <obs-frontend-api.h>

const QStringList default_preset_names({"Preset 1", "Preset 2", "Preset 3", "Preset 4", "Preset 5",
					"Preset 6", "Preset 7", "Preset 8", "Preset 9", "Preset 10"});

class PTZDevice : public QObject {
	Q_OBJECT

protected:
	std::string type;
	QStringListModel preset_names_model;

public:
	PTZDevice(std::string type) : QObject(), type(type)
	{
		preset_names_model.setStringList(default_preset_names);
	};
	~PTZDevice()
	{
	};

	static PTZDevice* make_device(OBSData config);

	virtual void pantilt(double pan, double tilt) { Q_UNUSED(pan); Q_UNUSED(tilt); }
	virtual void pantilt_rel(int pan, int tilt) { Q_UNUSED(pan); Q_UNUSED(tilt); }
	virtual void pantilt_stop() { }
	virtual void pantilt_home() { }
	virtual void zoom_stop() { }
	virtual void zoom_tele(double speed) { Q_UNUSED(speed); }
	virtual void zoom_wide(double speed) { Q_UNUSED(speed); }
	virtual void memory_set(int i) { Q_UNUSED(i); }
	virtual void memory_recall(int i) { Q_UNUSED(i); }
	virtual void memory_reset(int i) { Q_UNUSED(i); }
	virtual QAbstractListModel * presetModel() { return &preset_names_model; }

	virtual void set_config(OBSData ptz_config);
	virtual OBSData get_config();
};

class PTZSimulator : public PTZDevice {
	Q_OBJECT

public:
	PTZSimulator() : PTZDevice("sim") { };
	PTZSimulator(OBSData config) : PTZDevice("sim") { set_config(config); };

	void pantilt(double pan, double tilt) { blog(LOG_INFO, "%s %f %f", __func__, pan, tilt); }
	void pantilt_stop() { qDebug() << __func__; }
	void pantilt_home() { qDebug() << __func__; }
	void zoom_stop() { qDebug() << __func__; }
	void zoom_tele(double speed) { blog(LOG_INFO, "%s %f", __func__, speed); }
	void zoom_wide(double speed) { blog(LOG_INFO, "%s %f", __func__, -speed); }
};
