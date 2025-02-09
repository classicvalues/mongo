/**
 *    Copyright (C) 2021-present MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the Server Side Public License, version 1,
 *    as published by MongoDB, Inc.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    Server Side Public License for more details.
 *
 *    You should have received a copy of the Server Side Public License
 *    along with this program. If not, see
 *    <http://www.mongodb.com/licensing/server-side-public-license>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the Server Side Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */
#pragma once

#include "mongo/db/process_health/fault_facet.h"
#include "mongo/db/process_health/fault_facets_container.h"

namespace mongo {
namespace process_health {

/**
 * Interface to conduct periodic health checks.
 * Every instance of health observer is wired internally to update the state of the FaultManager
 * when a problem is detected.
 */
class HealthObserver {
public:
    virtual ~HealthObserver() = default;

    /**
     * Health observer of this type is unique and can only create the fault facet
     * of the same type.
     *
     * @return FaultFacetType of this health observer.
     */
    virtual FaultFacetType getType() const = 0;

    /**
     * Triggers health check.
     * It should be safe to invoke this method arbitrary often, the implementation
     * should prorate the invocations to avoid DoS.
     * The implementation may or may not block for the completion of the check, this remains
     * unspecified.
     *
     * @param factory Interface to get or create the factory of facets container.
     */
    virtual void periodicCheck(FaultFacetsContainerFactory& factory) = 0;
};

}  // namespace process_health
}  // namespace mongo
